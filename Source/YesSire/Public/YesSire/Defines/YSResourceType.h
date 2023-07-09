// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "YSResourceType.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EYSResourceType : uint8
{
	Coffer = 0,
	Society = 1,
	Ideology = 2,
	Millitary = 3,
	COUNT = 4
};
#define ERT EYSResourceType
class YESSIRE_API EYSResourceType_Func
{
public:

	inline static const TArray<EYSResourceType> ALL =
	{ ERT::Coffer, ERT::Society, ERT::Ideology, ERT::Millitary };
private:
	EYSResourceType_Func() {}
};
#undef ERT