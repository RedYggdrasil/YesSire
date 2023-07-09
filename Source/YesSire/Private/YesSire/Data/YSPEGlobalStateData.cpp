// Fill out your copyright notice in the Description page of Project Settings.


#include "YesSire/Data/YSPEGlobalStateData.h"
#include "YesSire/Defines/YS.h"

#define YS_MAX_PP  YS::MAX_PE_POINTS
#define YS_DECL  YS::NB_YEARS_FINAL_DECLINE

FYSPEGlobalStateData::FYSPEGlobalStateData()
{
}

void FYSPEGlobalStateData::GenerateNewTargetPE()
{
    NbHightDeltaSinceLastReset = 0;
    RedSpace::Noise TargetPENoise = RedSpace::Noise(FMath::RandRange(INT64_MIN, INT64_MAX));

    //During Gameplay ActualPE Is Updated before starting new year
    int32 LastIndex = ActualPE.Num() - 1;
    int32 StartValue = FMath::RoundHalfToZero(ActualPE[/*YearToPEArrIndex(CurrentYear)*/LastIndex].Y);
    //double expectedValue = TargetPENoise.eval(0, CurrentYear) * 10.0;
    if (YearToPEArrIndex(CurrentYear) >= LastIndex)
    {
        TargetPE[YearToPEArrIndex(CurrentYear)] = FVector2D(CurrentYear, StartValue);
    }

    //int32 Avrg = YS_MAX_PP * 0.5;
    for (int32 i = CurrentYear + 1; i <= EndYear; ++i)
    {
        //UE_LOG(LogTemp, Display, TEXT(" TargetPENoise[%d] : '%lf'"), i, TargetPENoise.eval(0, i) * 10.0);
        TargetPE[YearToPEArrIndex(i)] = FVector2D(i, ApplyCorrections(0, i, CurrentYear, StartValue));
    }
}

void FYSPEGlobalStateData::ResetPlan()
{
    Counselor = FYSCounselorData::CreateNewCounselor();
    NbHightDeltaSinceLastReset = 0;
    GenerateNewTargetPE();
}

bool FYSPEGlobalStateData::IncrementHightDelta()
{
    NbHightDeltaSinceLastReset += 1;
    return NbHightDeltaSinceLastReset > YS::MAX_HIGHT_DELTA_BEFORE_RESET;

}

FYSPEGlobalStateData FYSPEGlobalStateData::CreateGlobalState()
{
    FYSPEGlobalStateData globalState = FYSPEGlobalStateData();
    globalState.StartYear = FMath::RandRange(0, YS::MAX_START_LATER);
    globalState.EndYear = globalState.StartYear + YS::NB_YEARS_PER_SESSION;
    globalState.Technology = FMath::Clamp(YS::START_TECHNOLOGY + FMath::CeilToInt32((double)globalState.StartYear * YS::DELAYED_START_TECHNOLOGY), 0, 100);
    globalState.Counselor = FYSCounselorData::CreateNewCounselor();
    globalState.CurrentYear = globalState.StartYear;
    globalState.LastStartRule = globalState.CurrentYear;
    globalState.CurrentYearPeriod = 0;
    globalState.CardRemainThisPeriod = YS::NB_CARD_MAX_PER_PERIOD;
    //globalState
    globalState.ActualPE.Empty(globalState.GetTotalYears() + 1);

    globalState.ActualPE.Add(FVector2D(globalState.CurrentYear, FMath::RandRange(15, 25)));

    globalState.TargetPE.Empty(globalState.GetTotalYears() + 1);
    globalState.TargetPE.AddDefaulted(globalState.GetTotalYears() + 1);
    globalState.GenerateNewTargetPE();
    for (int i = 0; i < globalState.TargetPE.Num(); ++i)
    {
        //UE_LOG(LogTemp, Display, TEXT(" Target[%d] : '%s'"), i, *globalState.TargetPE[i].ToString());
    }
    return globalState;
}

double FYSPEGlobalStateData::ApplyCorrections(const RedSpace::Noise& Noise, int32 InYear, int32 InLastReset, double InLastResetValue)
{
    int32 Avrg = YS_MAX_PP * 0.5;
    int32 HAvrg = Avrg * 0.5;
    int32 midPoint = GetTotalYears() * 0.5;
    int32 ZeroBaseYear = InYear - StartYear;

    double Value = HAvrg + (Noise.eval(0, InYear * 0.05) * (HAvrg));
    double Multiplier = ((-1 / FMath::Square(midPoint * 2.0)) * (FMath::Square(ZeroBaseYear - midPoint))) + 1.8;
    //UE_LOG(LogTemp, Display, TEXT("Z to Val and Mul [%d, %lf, %lf] "), ZeroBaseYear, Value, Multiplier);
    Value *= Multiplier;

    int32 LastReset = InYear - InLastReset;
    int32 RemainingYears = EndYear - InYear;

    if (LastReset < 8)
    {
        Value = FMath::Lerp(InLastResetValue, Value, LastReset / 8.);
    }
    Value = FMath::Clamp(Value, 10, YS_MAX_PP - 10);
    if (RemainingYears < YS_DECL)
    {
        Value = Value * FMath::Lerp(0., 1., ((double)RemainingYears / (double)YS_DECL));
    }
    return Value;
}
#undef YS_MAX_PP
#undef YS_DECL