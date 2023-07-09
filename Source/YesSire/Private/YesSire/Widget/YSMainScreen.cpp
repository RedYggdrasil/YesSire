// Fill out your copyright notice in the Description page of Project Settings.


#include "YesSire/Widget/YSMainScreen.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Kismet/GameplayStatics.h"
#include "RS/RS.h"
#include "YesSire/Defines/YS.h"
#include "YesSire/GameplayFramework/YSGameState.h"
#include "YesSire/Style/YSStyleData.h"
#include "YesSire/Widget/YSGameOver.h"
#include "YesSire/Widget/YSHandWidget.h"
#include "YesSire/Widget/YSSplineGraph.h"
#include "YesSire/Widget/YSSessionGraph.h"

void UYSMainScreen::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	BW_SkipButton->OnClicked.AddUniqueDynamic(this, &ThisClass::OnSkipClicked);
}

void UYSMainScreen::UpdateGameState(const FYSPEData& InGameState)
{
	const FYSRuleStateData& RS = InGameState.RuleState;
	const FYSPEGlobalStateData& GS = InGameState.GlobalState;
	const FYESessionStatData& SS = InGameState.SessionStatistics;

	BW_GameOver->SetVisibility(ESlateVisibility::Hidden);
	BW_KingYes->SetColorAndOpacity(YSStyleI.PositiveColor);
	BW_KingYes->SetVisibility(ESlateVisibility::Hidden);
	BW_KingNo->SetColorAndOpacity(YSStyleI.ErrorColor);
	BW_KingNo->SetVisibility(ESlateVisibility::Hidden);

	BW_SkipButtonText->SetText(FText::FromString(GS.CurrentYearPeriod < (YS::NB_PERIOD_PER_YEAR - 1) ? "End season" : "End year"));
	BW_YearText->SetText(FText::FromString(FString::FromInt(GS.CurrentYear)));
	BW_EndYearText->SetText(FText::FromString(FString::FromInt(GS.EndYear)));
	BW_SeasonText->SetText(FText::FromString(YS::YEAR_PERIOD_DISPLAY_NAMES[GS.CurrentYearPeriod]));
	BW_KingState->SetText(FText::FromString(InGameState.RuleState.Ruler.GetLucidityText(GS.CurrentYearPeriod)));
	BW_KingState->SetColorAndOpacity(YSStyleI.MainActionWhiteColor);

	BW_NBCofferText->SetText(FText::FromString(FString::FromInt(RS.Resources[EYSResourceType::Coffer])));
	BW_NBCofferText->SetColorAndOpacity(ValueToColor(RS.Resources[EYSResourceType::Coffer]));
	BW_NBSocietyText->SetText(FText::FromString(FString::FromInt(RS.Resources[EYSResourceType::Society])));
	BW_NBSocietyText->SetColorAndOpacity(ValueToColor(RS.Resources[EYSResourceType::Society]));
	BW_NBIdeologyText->SetText(FText::FromString(FString::FromInt(RS.Resources[EYSResourceType::Ideology])));
	BW_NBIdeologyText->SetColorAndOpacity(ValueToColor(RS.Resources[EYSResourceType::Ideology]));
	BW_NBMillitaryText->SetText(FText::FromString(FString::FromInt(RS.Resources[EYSResourceType::Millitary])));
	BW_NBMillitaryText->SetColorAndOpacity(ValueToColor(RS.Resources[EYSResourceType::Millitary]));

	BW_NBTechnologyText->SetText(FText::FromString(FString::FromInt(GS.Technology)));

	BW_RulerNameText->SetText(FText::FromString(RS.Ruler.Name));
	BW_RulerNameText->SetColorAndOpacity(YSStyleI.MainActionWhiteColor);

	BW_CounselorNameText->SetText(FText::FromString(GS.Counselor.Name));
	BW_CounselorNameText->SetColorAndOpacity(YSStyleI.MainActionWhiteColor);


	FString HightDeltaText = FString::FromInt(GS.NbHightDeltaSinceLastReset) + "/" + FString::FromInt(YS::MAX_HIGHT_DELTA_BEFORE_RESET + 1);
	BW_NBHighDeltaText->SetText(FText::FromString(HightDeltaText));

	FLinearColor HightDeltaColor = GS.NbHightDeltaSinceLastReset == 0 ? YSStyleI.PositiveColor :
		(GS.NbHightDeltaSinceLastReset < (YS::MAX_HIGHT_DELTA_BEFORE_RESET + 1)) ? YSStyleI.WarningColor : YSStyleI.ErrorColor;
	BW_NBHighDeltaText->SetColorAndOpacity(HightDeltaColor);


	int32 nbReset = SS.CNbPlan - 1;
	FString PlanResetText = FString::FromInt(nbReset) + "/" + FString::FromInt(YS::MAX_RESET_PER_SESSION);
	BW_NBPlanResetText->SetText(FText::FromString(PlanResetText));

	FLinearColor PlanResetColor = nbReset == 0 ? YSStyleI.PositiveColor :
		(nbReset < YS::MAX_RESET_PER_SESSION) ? YSStyleI.WarningColor : YSStyleI.ErrorColor;
	BW_NBPlanResetText->SetColorAndOpacity(PlanResetColor);

	BW_SessionGraph->RedrawGraph(InGameState);

	BW_HandWidget->RedrawHand(InGameState.RuleState);

}

void UYSMainScreen::AnimateKingDied()
{
	BW_RulerNameText->SetColorAndOpacity(YSStyleI.ErrorColor);
}

void UYSMainScreen::AnimateCounselorDied()
{
	BW_CounselorNameText->SetColorAndOpacity(YSStyleI.ErrorColor);
}

void UYSMainScreen::AnimateKingDecision(bool bInDecision)
{
	if (bInDecision)
	{
		BW_KingYes->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
	else
	{
		BW_KingNo->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
}

void UYSMainScreen::ShowGameOver(bool bSucess)
{
	BW_GameOver->SetVisibility(ESlateVisibility::Visible);
}

void UYSMainScreen::OnSkipClicked()
{
	AYSGameState* GS = Cast<AYSGameState>(UGameplayStatics::GetGameState(GetWorld()));
	if (GS)
	{
		GS->ApplySkipButton();
	}
}

FLinearColor UYSMainScreen::ValueToColor(int32 InValue)
{
	int32 Half = YS::MAX_RESOURCE_VALUE * 0.5;
	int32 Delta = FMath::Abs(Half - InValue);

	int32 PositiveResourceThreashold = YS::MAX_RESOURCE_VALUE * 0.15;
	int32 NegativeResourceThreashold = YS::MAX_RESOURCE_VALUE * 0.35;
	if (InValue <= 0 || InValue >= YS::MAX_RESOURCE_VALUE)
	{
		return YSStyleI.ErrorColor;
	}
	else if (Delta < PositiveResourceThreashold)
	{
		return YSStyleI.PositiveColor;
	}
	else if (Delta > NegativeResourceThreashold)
	{
		return YSStyleI.WarningColor;
	}

	return YSStyleI.MainActionWhiteColor;
}
