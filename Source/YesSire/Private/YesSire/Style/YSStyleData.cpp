// Fill out your copyright notice in the Description page of Project Settings.


#include "YesSire/Style/YSStyleData.h"
#include "RS/RS.h"

const FYSStyleData FYSStyleData::DEFAULT = FYSStyleData::CreateDefault();

const FYSStyleData* FYSStyleData::ActiveStyle = &FYSStyleData::DEFAULT;
bool FYSStyleData::bIsStypeGame = false;

const FYSStyleData& FYSStyleData::Get()
{
	return *FYSStyleData::ActiveStyle;
}

void FYSStyleData::SetInGameStyle(const FYSStyleData& InData)
{
	if (FYSStyleData::bIsStypeGame)
	{
		UE_LOG(LogTemp, Error, TEXT(L_PATH "Unexpected Resetting of InGame Stype !"));
	}
	FYSStyleData::ActiveStyle = &InData;
	FYSStyleData::bIsStypeGame = true;
}

void FYSStyleData::ResetInGameStyle()
{
	if (!FYSStyleData::bIsStypeGame)
	{
		UE_LOG(LogTemp, Error, TEXT(L_PATH "Unexpected Reseting of InGame Stype !"));
	}
	FYSStyleData::ActiveStyle = &FYSStyleData::DEFAULT;
	FYSStyleData::bIsStypeGame = false;
}

FYSStyleData FYSStyleData::CreateDefault()
{
	FYSStyleData defaultData = FYSStyleData();
	defaultData.bIsDefault = true;
	return defaultData;
}