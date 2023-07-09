// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "YSPersonData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct YESSIRE_API FYSPersonData
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;
public:
	FYSPersonData();
};