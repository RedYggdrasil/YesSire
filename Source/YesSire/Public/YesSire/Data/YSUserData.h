// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "YesSire/Data/YSOptionData.h"
#include "YesSire/Data/YSPEData.h"
#include "YSUserData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct YESSIRE_API FYSUserData
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "Design")
	FYSPEData CurrentPEData;
	UPROPERTY(EditAnywhere, Category = "Design")
	FYSOptionData OptionData;
public:
	FYSUserData();
};
