// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "YSRuleEndType.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EYSRuleEndType : uint8
{
	RulerOldAge = 0,
	ResourceCriticalNegative = 1,
	ResourceCriticalPositive = 2,
	COUNT = 3
};
#define ERET EYSRuleEndType
class YESSIRE_API EYSRuleEndType_Func
{
public:

	inline static const TArray<ERET> ALL =
	{ ERET::RulerOldAge, ERET::ResourceCriticalNegative, ERET::ResourceCriticalPositive };
	static bool IsResourceCritical(ERET InType) { return InType == ERET::ResourceCriticalNegative || InType == ERET::ResourceCriticalPositive; }
private:
	EYSRuleEndType_Func() {}
};
#undef ERT
