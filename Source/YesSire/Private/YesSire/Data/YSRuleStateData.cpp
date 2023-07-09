// Fill out your copyright notice in the Description page of Project Settings.


#include "YesSire/Data/YSRuleStateData.h"
#include "YesSire/Card/YSCardManager.h"
#include "YesSire/Defines/YS.h"
#include "YesSire/GameplayFramework/YSGameState.h"

FYSRuleStateData::FYSRuleStateData()
{
	int32 c = (int32)EYSResourceType::COUNT;
	Resources.Reserve(c);
	for (int i = 0; i < c; ++i)
	{
		Resources.Add((EYSResourceType)i, 0);
	}
}

void FYSRuleStateData::PullFromDeck()
{
	int32 nbCardThisTurn = FMath::Min(YS::NB_CARD_PULL_PER_YEAR, this->Deck.Num());

	for (int32 i = 0; i < nbCardThisTurn; ++i)
	{
		const FYSCardData& Card = this->Deck[0];
		Hand.Add(Card);
		Deck.RemoveAt(0);
	}
}
inline bool FYSRuleStateData::IsRuleEnd(EYSRuleEndType& EOutRuleEndType, EYSResourceType& EOutPotencialResource) const
{
	EOutRuleEndType = EYSRuleEndType::COUNT;
	EOutPotencialResource = EYSResourceType::COUNT;
	if (this->Deck.Num() < 1)
	{
		EOutRuleEndType = EYSRuleEndType::RulerOldAge;
		return true;
	}
	for (const TPair<EYSResourceType, int32>& Pair : Resources)
	{
		if (Pair.Value < 1)
		{
			EOutRuleEndType = EYSRuleEndType::ResourceCriticalNegative;
			EOutPotencialResource = Pair.Key;
			return true;
		}
		if (Pair.Value >= YS::MAX_RESOURCE_VALUE)
		{
			EOutRuleEndType = EYSRuleEndType::ResourceCriticalPositive;
			EOutPotencialResource = Pair.Key;
			return true;
		}
	}
	return false;
}
int32 FYSRuleStateData::GetYearCulativePEScore() const
{
	int32 CumulativeScore = 0;
	int32 MidpointResource = YS::MAX_RESOURCE_VALUE * 0.5;
	int32 PositiveResourceThreashold = YS::MAX_RESOURCE_VALUE * 0.15;
	int32 NegativeResourceThreashold = YS::MAX_RESOURCE_VALUE * 0.35;
	for (const TPair<EYSResourceType, int32>& Pair : Resources)
	{
		int32 ResourceDelta = FMath::Abs(MidpointResource - Pair.Value);
		if (ResourceDelta < PositiveResourceThreashold)
		{
			//*0.5 is there to compensate kingdom is more ofter at equilibrium than not
			CumulativeScore += (PositiveResourceThreashold - ResourceDelta) *0.5;
		}
		else if (ResourceDelta > NegativeResourceThreashold)
		{
			CumulativeScore -= ResourceDelta - NegativeResourceThreashold;
		}
	}
	CumulativeScore = FMath::Clamp(CumulativeScore, -YS::MAX_PE_POINT_CHANGE_PER_TURN, YS::MAX_PE_POINT_CHANGE_PER_TURN);
	return CumulativeScore;

}
FYSRuleStateData FYSRuleStateData::NewRuleState(const TArray<FYSCardData>& InDeck)
{
	FYSRuleStateData State = FYSRuleStateData();
	State.Hand.Empty(YS::NB_CARD_PULL_PER_YEAR);
	State.Deck = InDeck;

	int32 c = (int32)EYSResourceType::COUNT;
	for (int i = 0; i < c; ++i)
	{
		State.Resources[(EYSResourceType)i] = YS::NB_DEFAULT_RESOURCE_VALUE;
	}
	State.Ruler = FYSRulerData::AutoGenerateRuler();
	return State;
}

bool FYSRuleStateData::RulerDecideCardPlay(const FYSCardData& InCard, int32 InYearPeriod)
{
	TArray<EYSResourceType> Priority = TArray<EYSResourceType>();
	TArray<int32> PriorityAbs = TArray<int32>();
	//True is Up
	TMap<EYSResourceType, bool> Goal = TMap<EYSResourceType, bool>();

	int32 TargetResource = YS::MAX_RESOURCE_VALUE * 0.5;
	for (const TPair<EYSResourceType, int32>& Pair : Resources)
	{
		bool inserted = false;
		int32 ABSDelta = FMath::Abs(Pair.Value - TargetResource);
		for (int32 i = 0; i < Priority.Num(); ++i)
		{
			if (ABSDelta > PriorityAbs[i])
			{
				Priority.Insert(Pair.Key, i);
				PriorityAbs.Insert(ABSDelta, i);
				Goal.Add(Pair.Key, Pair.Value < TargetResource);
				inserted = true;
				break;
			}
		}
		if (!inserted)
		{
			Priority.Add(Pair.Key);
			PriorityAbs.Add(ABSDelta);
			Goal.Add(Pair.Key, Pair.Value < TargetResource);
		}
	}
	bool wouldLike = false;
	for (EYSResourceType Prior : Priority)
	{
		if (InCard.ResourceModifiers.Contains(Prior))
		{
			const FYSActionValuesData& Vals = InCard.ResourceModifiers[Prior];
			if (Vals.YesValue > 0 == Goal[Prior])
			{
				wouldLike = true;
				break;
			}
			else if (Vals.NoValue > 0 == Goal[Prior])
			{
				wouldLike = false;
				break;
			}
			continue;
		}
	}
	double LuciditySucess = 0.55;
	double Lucidity = FMath::RandRange(0.0, 0.5) + FMath::RandRange(0.0, Ruler.Lucidity[InYearPeriod]);
	if (Lucidity < LuciditySucess)
	{
		wouldLike = !wouldLike;
	}
	return wouldLike;
}
