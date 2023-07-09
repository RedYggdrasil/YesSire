// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class YESSIRE_API YS
{
public:
	static const TArray<FString> YEAR_PERIOD_DISPLAY_NAMES;
	inline static const int32 NB_PERIOD_PER_YEAR = 4;
	inline static const int32 NB_CARD_MAX_PER_PERIOD = 2;

	inline static const double CARD_ANIM_ACTION_PLAY_TIME = 0.5;
	inline static const double CARD_ANIM_ACTION_DISCARD_TIME = 0.5;
	inline static const double CARD_ANIM_ACTION_PULL_TIME = 0.5;
	inline static const double CARD_ANIM_ACTION_ONHAND_TIME = 0.5;

	inline static const double CARD_ANIM_POST_ACTION_FREEZ_TIME = 0.15;
public:
	inline static const int32 NB_DEFAULT_RESOURCE_VALUE = 50;
public:
	inline static const int32 NB_YEARS_PER_SESSION = 100;

	inline static const int32 NB_CARD_PULL_PER_YEAR = 6;

	inline static const int32 NB_MIN_RULER_NATURAL_LIFE = 35;
	inline static const int32 NB_MAX_RULER_NATURAL_LIFE = 50;

	inline static const int32 HIGHT_DELTA_THREASHOLD = 20;
	inline static const int32 MAX_HIGHT_DELTA_BEFORE_RESET = 2;
	inline static const int32 MAX_RESET_PER_SESSION = 2;

public:
	inline static const int32 MAX_PE_POINT_CHANGE_PER_TURN = 15;
	inline static const int32 MAX_RESOURCE_VALUE = 100;

	inline static const int32 MAX_PE_POINTS = 100;
	inline static const int32 NB_YEARS_FINAL_DECLINE = 35;

	inline static const int32 MAX_START_LATER = 155;
	inline static const int32 START_TECHNOLOGY = 05;
	inline static const double DELAYED_START_TECHNOLOGY = 0.1;
public:
	inline static const double RULER_LUCIDITY_PROGRESSION = 0.05;
	inline static const double RULER_LUCIDITY_PROGRESSION_DELTA = 0.05;

	inline static const TArray<double> RULER_START_LUCIDITY = { 0.4, 0.5, 0.4, 0.4 };
	inline static const TArray<double> RULER_START_LUCIDITY_DELTA = { 0.2, 0.3, 0.2, 0.35 };
	static const TArray<FString> RULER_NAMES;
	static const TArray<FString> COUNSELOR_NAMES;
public:
	static FString RandomRulerName();
	static FString RandomCounselorName();
private:
	YS() {};
};
