// Fill out your copyright notice in the Description page of Project Settings.


#include "YesSire/Defines/YSCardActionType.h"
#include "RS/RS.h"
#include "YesSire/Defines/YS.h"

double EYSCardActionType_Func::GetAnimLenght(EYSCardActionType EAT)
{
	switch (EAT)
	{
	case EYSCardActionType::PlayYes:
		return YS::CARD_ANIM_ACTION_PLAY_TIME;
	case EYSCardActionType::PlayNo:
		return YS::CARD_ANIM_ACTION_PLAY_TIME;
	case EYSCardActionType::OnDiscard:
		return YS::CARD_ANIM_ACTION_DISCARD_TIME;
	case EYSCardActionType::OnPulled:
		return YS::CARD_ANIM_ACTION_PULL_TIME;
	case EYSCardActionType::OnHand:
		return YS::CARD_ANIM_ACTION_ONHAND_TIME;
	default:
		UE_LOG(LogTemp, Error, TEXT(L_PATH "Switch case '%s' unimplemented !"), *UEnum::GetValueAsString(EAT));
		break;
	}
    return 0.0;
}
