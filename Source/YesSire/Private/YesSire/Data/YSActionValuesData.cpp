// Fill out your copyright notice in the Description page of Project Settings.


#include "YesSire/Data/YSActionValuesData.h"
#include "RS/RS.h"

FYSActionValuesData::FYSActionValuesData()
{
}

int32 FYSActionValuesData::GetValue(EYSCardActionType EInCardActionType) const
{
	switch (EInCardActionType)
	{
	case EYSCardActionType::PlayYes:
		return this->YesValue;
	case EYSCardActionType::PlayNo:
		return this->NoValue;
	case EYSCardActionType::OnDiscard:
		return this->DiscardValue;
	case EYSCardActionType::OnPulled:
		return 0;
	case EYSCardActionType::OnHand:
		return 0;
	default:
		UE_LOG(LogTemp, Error, TEXT(L_PATH "Unimplemented case '%s' in switch !"), *UEnum::GetValueAsString(EInCardActionType));
		return 0;
	}
}
