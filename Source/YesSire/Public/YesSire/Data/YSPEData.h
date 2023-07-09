// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "YesSire/Data/YSPEGlobalStateData.h"
#include "YesSire/Data/YSRuleStateData.h"
#include "YesSire/Data/YESessionStatData.h"
#include "YSPEData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct YESSIRE_API FYSPEData
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FYSRuleStateData RuleState;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FYSPEGlobalStateData GlobalState;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FYESessionStatData SessionStatistics;

public:
	FYSPEData();
	bool IsInitialized() const { return false; }
	void CreateNewRule(const TArray<struct FYSCardData>& InDeck);
public:
	static FYSPEData CreatePESession(const TArray<FYSCardData>& InDeck);
};
