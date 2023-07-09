// Fill out your copyright notice in the Description page of Project Settings.


#include "YesSire/Data/YSPEData.h"
#include "YesSire/Data/YSCardData.h"

FYSPEData::FYSPEData()
{
}

void FYSPEData::CreateNewRule(const TArray<struct FYSCardData>& InDeck)
{
    this->RuleState = FYSRuleStateData::NewRuleState(InDeck);
}

FYSPEData FYSPEData::CreatePESession(const TArray<struct FYSCardData>& InDeck)
{
    FYSPEData PEData = FYSPEData();
    PEData.CreateNewRule(InDeck);
    PEData.GlobalState = FYSPEGlobalStateData::CreateGlobalState();
    PEData.SessionStatistics = FYESessionStatData::CreateNewSessionStats();
    return PEData;
}

