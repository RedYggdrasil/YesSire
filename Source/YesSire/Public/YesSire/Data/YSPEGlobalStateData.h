// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RS/Tools/OpenSimplexNoise.h"
#include "YesSire/Data/YSCounselorData.h"
#include "YSPEGlobalStateData.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct YESSIRE_API FYSPEGlobalStateData
{
	GENERATED_USTRUCT_BODY()
protected:
	//RedSpace::Noise TargetPENoise;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Technology;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FYSCounselorData Counselor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 StartYear;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 EndYear;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 LastStartRule;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrentYear;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrentYearPeriod;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CardRemainThisPeriod;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 NbHightDeltaSinceLastReset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FVector2D> TargetPE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FVector2D> ActualPE;
public:
	FYSPEGlobalStateData();
	int32 GetRestingYears() const { return EndYear - CurrentYear; }
	int32 GetTotalYears() const { return EndYear - StartYear; }
	int32 YearToPEArrIndex(int32 InYear) const { return InYear - StartYear; }
	void GenerateNewTargetPE();
	void ResetPlan();

	bool IncrementHightDelta();
public:
	static FYSPEGlobalStateData CreateGlobalState();

protected:
	double ApplyCorrections(const RedSpace::Noise& Noise, int32 InYear, int32 InLastReset, double InLastResetValue);
};