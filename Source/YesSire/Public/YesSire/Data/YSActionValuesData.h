// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "YesSire/Defines/YSCardActionType.h"
#include "YSActionValuesData.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct YESSIRE_API FYSActionValuesData
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 YesValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 NoValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 DiscardValue;
public:
	FYSActionValuesData();

	int32 GetValue(EYSCardActionType EInCardActionType) const;
};
