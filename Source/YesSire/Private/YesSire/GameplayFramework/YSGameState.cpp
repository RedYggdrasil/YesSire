// Fill out your copyright notice in the Description page of Project Settings.


#include "YesSire/GameplayFramework/YSGameState.h"
#include "RS/RS.h"
#include "YesSire/Card/YSCardManager.h"
#include "YesSire/Defines/YS.h"
#include "YesSire/GameplayFramework/YSPlayerController.h"
#include "YesSire/Save/YSSaveGame.h"
#include "YesSire/Widget/YSMainScreen.h"

void AYSGameState::BeginPlay()
{
	Super::BeginPlay();

	ULocalPlayer* localPlayer = GetWorld()->GetFirstLocalPlayerFromController();
	APlayerController* pc = localPlayer->GetPlayerController(GetWorld());
	Mpc = Cast<AYSPlayerController>(pc);
	UYSMainScreen* screen = Mpc->SetupScreen(ScreenClass);
	SetAnimState(EGameStateAnimType::None);

	CardManager = NewObject<UYSCardManager>()->InitUObj(this);

	CurrentSave = UYSSaveGame::LoadSave();
	const FYSUserData UserData = CurrentSave->GetUserData();
	Mpc->ApplyOptions(UserData.OptionData);

	if (UserData.CurrentPEData.IsInitialized())
	{
		LoadSession(UserData.CurrentPEData);
	}
	else
	{
		StartNewSession();
	}
}

void AYSGameState::LoadSession(const FYSPEData& InPEData)
{
	PEData = InPEData;
	StartNextTurn();
}

void AYSGameState::StartNewSession()
{
	PEData = FYSPEData::CreatePESession(CardManager->CreateDeck());
	PrepareNextTurn(false);
}

void AYSGameState::StartEndTurn()
{
	EndTurnProcedure();
}

void AYSGameState::EndTurnProcedure()
{
	Mpc->UpdateScreen(PEData);
	if (PEData.RuleState.Hand.Num() > 0)
	{
		SetAnimState(EGameStateAnimType::DiscardCard);
		CardManager->ApplyCardAction(EYSCardActionType::OnDiscard, 0);
		return;
	}
	EYSRuleEndType ERuleEndType;
	EYSResourceType ERessourceType;
	if (PEData.RuleState.IsRuleEnd(ERuleEndType, ERessourceType))
	{
		ApplyRuleEnd(ERuleEndType, ERessourceType);
		return;
	}
	FYSPEGlobalStateData& GS = PEData.GlobalState;
	FYESessionStatData& SS = PEData.SessionStatistics;
	int32 TargetPE = FMath::RoundHalfToZero(GS.TargetPE[GS.YearToPEArrIndex(GS.CurrentYear+1)].Y);
	UE_LOG(LogTemp, Warning, TEXT("TargetPE '%s'"), *GS.TargetPE[GS.YearToPEArrIndex(GS.CurrentYear + 1)].ToString());
	UE_LOG(LogTemp, Warning, TEXT("LastGamePE '%s'"), *GS.ActualPE[GS.YearToPEArrIndex(GS.CurrentYear)].ToString());

	//We need to generate the new PE and go to next Year
	if (GS.ActualPE.Num() == GS.YearToPEArrIndex(GS.CurrentYear + 1))
	{
		int32 LastGamePE = FMath::RoundHalfToZero(GS.ActualPE[GS.YearToPEArrIndex(GS.CurrentYear)].Y);
		//We don't get points for having default perfect alignement
		int32 PointChangeFromRuleState = GS.LastStartRule != GS.CurrentYear ? PEData.RuleState.GetYearCulativePEScore() : 0;
		int32 NewPEPoint = LastGamePE + PointChangeFromRuleState;
		GS.ActualPE.Add(FVector2D(GS.CurrentYear + 1, NewPEPoint));

		UE_LOG(LogTemp, Warning, TEXT("Add ActualPE [%d, %d] ( last %d, change %d) "), GS.CurrentYear + 1, NewPEPoint, LastGamePE, PointChangeFromRuleState);
		int32 ComputedDelta = FMath::Abs(TargetPE - NewPEPoint);
		SS.CPETargetDelta += ComputedDelta;

		bool bHighDelta = false;
		if (ComputedDelta > YS::HIGHT_DELTA_THREASHOLD)
		{
			if (PEData.GlobalState.IncrementHightDelta())
			{
				ApplyPlanEnd();
				return;
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("PlanEnd Already setup (normal if reset)"));
	}

	GS.CurrentYear += 1;
	GS.CurrentYearPeriod = 0;
	GS.CardRemainThisPeriod = YS::NB_CARD_MAX_PER_PERIOD;
	GS.Technology += 1;

	if (GS.CurrentYear + 1 == PEData.GlobalState.EndYear)
	{
		ApplySessionEnd();
	}
	else
	{
		PrepareNextTurn(false);
	}
}


void AYSGameState::PrepareNextTurn(bool bSkipSave)
{
	PEData.RuleState.PullFromDeck();
	if (!bSkipSave)
	{
		CurrentSave->GetUserData().CurrentPEData = PEData;
		CurrentSave->CommitSave();
	}
	StartNextTurn();
}

void AYSGameState::StartNextTurn()
{
	Screen()->UpdateGameState(PEData);
}

void AYSGameState::ApplyRuleEnd(EYSRuleEndType EInRuleEndType, EYSResourceType EInPotencialAssociatedResource)
{
	//UE_LOG(LogTemp, Error, TEXT(L_PATH "Unimplemented Exception !"));
	SetAnimState(EGameStateAnimType::RuleEnd);

	Screen()->UpdateGameState(PEData);
	Screen()->AnimateKingDied();

	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	TimerHandle = FTimerHandle();
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ThisClass::ContinueProcedureAfterAnimation, 0.5 + YS::CARD_ANIM_POST_ACTION_FREEZ_TIME, false);

}

void AYSGameState::ApplySelectedCard(int32 InSelectedCardIndex)
{
	SetAnimState(EGameStateAnimType::PlayCard);
	bool Result = PEData.RuleState.RulerDecideCardPlay(PEData.RuleState.Hand[InSelectedCardIndex], PEData.GlobalState.CurrentYearPeriod);
	
	CardManager->ApplyCardAction(Result ? EYSCardActionType::PlayYes : EYSCardActionType::PlayNo, InSelectedCardIndex);
	Screen()->AnimateKingDecision(Result);
}

void AYSGameState::ApplySkipButton()
{
	ApplyPeriodEnd();
}

void AYSGameState::OnAppliedSelectedCard()
{
	if (PEData.RuleState.Hand.Num() < 1)
	{
		EndTurnProcedure();
	}
	else if (PEData.GlobalState.CardRemainThisPeriod < 1)
	{
		ApplyPeriodEnd();
	}
	else
	{
		Mpc->UpdateScreen(PEData);
	}
}

void AYSGameState::ApplyPeriodEnd()
{
	if (PEData.GlobalState.CurrentYearPeriod >= (YS::NB_PERIOD_PER_YEAR - 1))
	{
		EndTurnProcedure();
	}
	else
	{
		++PEData.GlobalState.CurrentYearPeriod;
		PEData.GlobalState.CardRemainThisPeriod = YS::NB_CARD_MAX_PER_PERIOD;
		Mpc->UpdateScreen(PEData);
	}
}

void AYSGameState::ApplyPlanEnd()
{
	SetAnimState(EGameStateAnimType::PlanEnd);
	Screen()->UpdateGameState(PEData);
	Screen()->AnimateCounselorDied();

	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	TimerHandle = FTimerHandle();
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ThisClass::ContinueProcedureAfterAnimation, 0.5 + YS::CARD_ANIM_POST_ACTION_FREEZ_TIME, false);

}

void AYSGameState::ApplySessionEnd()
{
	Screen()->ShowGameOver(true);
}

void AYSGameState::OnCardActionApplied(int32 InCardIndex, double InCardAnimTime, bool bInCardDiscarded, const TMap<EYSResourceType, int32>& ResourceChanged)
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	TimerHandle = FTimerHandle();
	Mpc->AnimateCardDiscard(InCardIndex, InCardAnimTime, bInCardDiscarded, ResourceChanged);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ThisClass::ContinueProcedureAfterAnimation, InCardAnimTime + YS::CARD_ANIM_POST_ACTION_FREEZ_TIME, false);
}

void AYSGameState::OnAnimatedRuleEnd()
{
	UE_LOG(LogTemp, Warning, TEXT("OnAnimatedRuleEnd"));
	PEData.CreateNewRule(CardManager->CreateDeck());
	++PEData.SessionStatistics.CNbMonarch;
	PEData.GlobalState.LastStartRule = PEData.GlobalState.CurrentYear;
	EndTurnProcedure();
}

void AYSGameState::OnAnimatedPlanEnd()
{
	UE_LOG(LogTemp, Warning, TEXT("OnAnimatedPlanEnd"));
	PEData.GlobalState.ResetPlan();
	++PEData.SessionStatistics.CNbPlan;
	++PEData.SessionStatistics.CNbConcellor;
	EndTurnProcedure();
}

void AYSGameState::SetAnimState(EGameStateAnimType InAnimState)
{
	if (Mpc && Screen())
	{
		Screen()->SetVisibility(((InAnimState == EGameStateAnimType::None) ? ESlateVisibility::Visible : ESlateVisibility::HitTestInvisible));
	}
	CurrentAnimation = InAnimState;
}

UYSMainScreen* AYSGameState::Screen() const
{
	return Mpc->GetScreen();
}

void AYSGameState::ContinueProcedureAfterAnimation()
{
	EGameStateAnimType PastAnimation = CurrentAnimation;
	SetAnimState(EGameStateAnimType::None);

	switch (PastAnimation)
	{
	case EGameStateAnimType::DrawCard:
		break;
	case EGameStateAnimType::PlayCard:
		OnAppliedSelectedCard();
		return;
	case EGameStateAnimType::DiscardCard:
		EndTurnProcedure();
		return;
	case EGameStateAnimType::RuleEnd:
		OnAnimatedRuleEnd();
		return;
	case EGameStateAnimType::PlanEnd:
		OnAnimatedPlanEnd();
		return;
	case EGameStateAnimType::None:
		break;
	case EGameStateAnimType::COUNT:
		break;
	default:
		break;
	}
	UE_LOG(LogTemp, Error, TEXT(L_PATH "Unhandled continue procedure after animation '%s'"), *UEnum::GetValueAsString(PastAnimation));
}
