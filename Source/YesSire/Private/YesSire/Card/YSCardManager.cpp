// Fill out your copyright notice in the Description page of Project Settings.


#include "YesSire/Card/YSCardManager.h"
#include "RS/Tools/RMath.h"
#include "YesSire/Data/YSCardData.h"
#include "YesSire/Defines/YS.h"
#include "YesSire/Defines/YSResourceType.h"
#include "YesSire/GameplayFramework/YSGameState.h"

UYSCardManager* UYSCardManager::InitUObj(AYSGameState* InGameState)
{
	GameState = InGameState;
	return this;
}

TArray<struct FYSCardData> UYSCardManager::CreateDeck() const
{
	TArray<struct FYSCardData> Deck = TArray<struct FYSCardData>();
	int32 nbMaxRulerLife = FMath::RandRange(YS::NB_MIN_RULER_NATURAL_LIFE, YS::NB_MAX_RULER_NATURAL_LIFE);
	int32 DeckCount = nbMaxRulerLife * YS::NB_CARD_PULL_PER_YEAR;
	Deck.Reserve(DeckCount);

	for (int i = 0; i < DeckCount; ++i)
	{
		Deck.Emplace(CreateCard());
	}
	return Deck;
}

FYSCardData UYSCardManager::CreateCard() const
{
	FYSCardData NewCard = FYSCardData();
	int32 nbCostType = RMath::WeightedDecision(TArray<int32>{ 05, 55, 30, 10});
	TArray<EYSResourceType> PossibleResourcesTypes = EYSResourceType_Func::ALL;

	TArray<int32> IndexToCost		= { 05, 10, 20, 30 };
	TArray<int32> IndexToCostWeight = { 20, 30, 40, 10 };

	TArray<int32> IndexToBene		= { 10, 15, 25, 30 };
	TArray<int32> IndexToBeneWeight = { 20, 30, 40, 10 };

	for (int32 i = 0; i < nbCostType; ++i)
	{
		int32 TypeIndex = FMath::RandRange(0, PossibleResourcesTypes.Num() - 1);
		EYSResourceType CostType = PossibleResourcesTypes[TypeIndex];
		PossibleResourcesTypes.RemoveAt(TypeIndex);
		if (!NewCard.ResourceModifiers.Contains(CostType))
		{
			NewCard.ResourceModifiers.Add(CostType, FYSActionValuesData());
		}
		NewCard.ResourceModifiers[CostType].YesValue = -IndexToCost[RMath::WeightedDecision(IndexToCostWeight)];
		NewCard.ResourceModifiers[CostType].NoValue = +(RMath::WeightedDecision(TArray<int32>{ 80, 20 }) ?
			(FMath::Clamp(NewCard.ResourceModifiers[CostType].YesValue * 0.5, 05, 100)) : 0);
		NewCard.ResourceModifiers[CostType].DiscardValue = FMath::RandBool() ?
			(FMath::Clamp(NewCard.ResourceModifiers[CostType].YesValue * 0.25, 05, 100)) : 0;
	}

	int32 nbBenefType = FMath::RandRange(0, PossibleResourcesTypes.Num() - 1);

	for (int32 i = 0; i < nbBenefType; ++i)
	{
		int32 TypeIndex = FMath::RandRange(0, PossibleResourcesTypes.Num() - 1);
		EYSResourceType CostType = PossibleResourcesTypes[TypeIndex];
		PossibleResourcesTypes.RemoveAt(TypeIndex);
		if (!NewCard.ResourceModifiers.Contains(CostType))
		{
			NewCard.ResourceModifiers.Add(CostType, FYSActionValuesData());
		}
		NewCard.ResourceModifiers[CostType].YesValue = +IndexToBene[RMath::WeightedDecision(IndexToBeneWeight)];
		NewCard.ResourceModifiers[CostType].NoValue = -(RMath::WeightedDecision(TArray<int32>{ 80, 20 }) ?
			(FMath::Clamp(NewCard.ResourceModifiers[CostType].YesValue * 0.5, 05, 100)) : 0);
		NewCard.ResourceModifiers[CostType].DiscardValue = FMath::RandBool() ?
			(FMath::Clamp(NewCard.ResourceModifiers[CostType].YesValue * 0.25, 05, 100)) : 0;
	}

	return NewCard;
}

void UYSCardManager::ApplyCardAction(EYSCardActionType EInCardActionType, int32 InCardIndex)
{
	bool StateChanged = false;
	FYSPEData& PEData = GameState->GetPEData();
	FYSCardData card = PEData.RuleState.Hand[InCardIndex];

	TMap<EYSResourceType, int32> ChangeResume;
	if(card.OnDiscard.Num() > 0)
	{
		//Not Implemented
	}

	for (const TPair<EYSResourceType, FYSActionValuesData>& Pair : card.ResourceModifiers)
	{
		if (Pair.Value.GetValue(EInCardActionType) != 0)
		{
			if (!ChangeResume.Contains(Pair.Key))
			{
				ChangeResume.Add(Pair.Key, 0);
			}
			ChangeResume[Pair.Key] += Pair.Value.GetValue(EInCardActionType);
		}
	}
	for (const TPair<EYSResourceType, int32>& Pair : ChangeResume)
	{
		StateChanged = true;
		PEData.RuleState.Resources[Pair.Key] += Pair.Value;
	}

	if (EYSCardActionType_Func::IsPlay(EInCardActionType))
	{
		--PEData.GlobalState.CardRemainThisPeriod;
		StateChanged = true;
	}

	bool CardConsumed = false;
	if (EYSCardActionType_Func::ConsumeCard(EInCardActionType))
	{
		StateChanged = CardConsumed = true;
		PEData.RuleState.Hand.RemoveAt(InCardIndex);
	}
	if (StateChanged)
	{
		GameState->OnCardActionApplied(InCardIndex, EYSCardActionType_Func::GetAnimLenght(EInCardActionType), CardConsumed, ChangeResume);
	}
}
