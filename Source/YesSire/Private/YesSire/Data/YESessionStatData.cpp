// Fill out your copyright notice in the Description page of Project Settings.


#include "YesSire/Data/YESessionStatData.h"

FYESessionStatData::FYESessionStatData()
{
}

FYESessionStatData FYESessionStatData::CreateNewSessionStats()
{
    FYESessionStatData Stats = FYESessionStatData();
    Stats.CNbMonarch = 1;
    Stats.CNbConcellor = 1;
    Stats.CNbPlan = 1;
    Stats.CPETargetDelta = 0;
    return Stats;
}
