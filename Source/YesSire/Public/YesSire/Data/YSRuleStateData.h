// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "YesSire/Data/YSCardData.h"
#include "YesSire/Data/YSRulerData.h"
#include "YesSire/Defines/YSRuleEndType.h"
#include "YesSire/Defines/YSResourceType.h"
#include "YSRuleStateData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct YESSIRE_API FYSRuleStateData
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FYSCardData> Hand;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FYSCardData> Deck;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FYSRulerData Ruler;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EYSResourceType, int32> Resources;

public:
	FYSRuleStateData();

	void PullFromDeck();

	inline bool IsRuleEnd() const { EYSRuleEndType _;  EYSResourceType _2;  return IsRuleEnd(_, _2); }
	bool IsRuleEnd(EYSRuleEndType& EOutRuleEndType, EYSResourceType& EOutPotencialResource) const;
	int32 GetYearCulativePEScore() const;
public:
	static FYSRuleStateData NewRuleState(const TArray<FYSCardData>& InDeck);
	bool RulerDecideCardPlay(const FYSCardData& InCard, int32 InYearPeriod);
};