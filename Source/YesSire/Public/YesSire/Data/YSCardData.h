// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "YesSire/Data/YSActionValuesData.h"
#include "YesSire/Defines/YSResourceType.h"
#include "YSCardData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct YESSIRE_API FYSCardData
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EYSResourceType, FYSActionValuesData> ResourceModifiers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSet<FString> OnPulled;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSet<FString> OnHand;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSet<FString> OnYes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSet<FString> OnNo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSet<FString> OnDiscard;

public:
	FYSCardData();
};
