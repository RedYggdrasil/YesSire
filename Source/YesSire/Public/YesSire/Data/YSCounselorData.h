// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "YesSire/Data/YSPersonData.h"
#include "YSCounselorData.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct YESSIRE_API FYSCounselorData : public FYSPersonData
{
	GENERATED_USTRUCT_BODY()
public:
public:
	FYSCounselorData();
public:
	static FYSCounselorData CreateNewCounselor();
};