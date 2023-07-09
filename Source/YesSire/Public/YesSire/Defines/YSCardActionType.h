// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "YSCardActionType.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EYSCardActionType : uint8
{
	PlayYes = 0,
	PlayNo = 1,
	OnDiscard = 2,
	OnPulled = 3,
	OnHand = 4,
	COUNT = 5
};

#define ECAT EYSCardActionType
class YESSIRE_API EYSCardActionType_Func
{
public:

	inline static const TArray<EYSCardActionType> ALL =
	{ ECAT::PlayYes, ECAT::PlayNo, ECAT::OnDiscard, ECAT::OnPulled, ECAT::OnHand };
	inline static bool IsPlay(EYSCardActionType EAT) { return (uint8)EAT <= (uint8)ECAT::PlayNo; }
	inline static bool ConsumeCard(EYSCardActionType EAT) { return (uint8)EAT <= (uint8)ECAT::OnDiscard; }
	static double GetAnimLenght(EYSCardActionType EAT);
private:
	EYSCardActionType_Func() {}
};
#undef ECAT
