// Fill out your copyright notice in the Description page of Project Settings.


#include "YesSire/Data/YSCounselorData.h"
#include "YesSire/Defines/YS.h"

FYSCounselorData::FYSCounselorData()
:FYSPersonData()
{
}

FYSCounselorData FYSCounselorData::CreateNewCounselor()
{
    FYSCounselorData Counselor = FYSCounselorData();
    Counselor.Name = YS::RandomCounselorName();
    return Counselor;
}
