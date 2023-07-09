// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "YESessionStatData.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct YESSIRE_API FYESessionStatData
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CNbMonarch;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CNbConcellor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CNbPlan;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double CPETargetDelta;
public:
	FYESessionStatData();

public:
	static FYESessionStatData CreateNewSessionStats();
};