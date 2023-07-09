// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "YesSire/Data/YSPersonData.h"
#include "YSRulerData.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct YESSIRE_API FYSRulerData : public FYSPersonData
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<double>/*[4]*/ Lucidity; //[Morning, Noon, Afternoon, Night] [0, 1]
public:
	FYSRulerData();
	void AutoProgress(int32 InNbYears = 1);
	void Progress(const TArray<double>& InProgression);
	FString GetLucidityText(int32 InPeriod) const;
public:
	static FYSRulerData AutoGenerateRuler();
	static FYSRulerData NewRuler(const FString& Name, const TArray<double>& InLucidity);
};