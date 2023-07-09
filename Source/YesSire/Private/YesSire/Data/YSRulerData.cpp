// Fill out your copyright notice in the Description page of Project Settings.


#include "YesSire/Data/YSRulerData.h"
#include "YesSire/Defines/YS.h"

FYSRulerData::FYSRulerData()
:FYSPersonData()
{
	Lucidity.AddDefaulted(4);
}

void FYSRulerData::AutoProgress(int32 InNbYears)
{
	TArray<double> Progression = TArray<double>();
	Progression.AddDefaulted(4);
	for (int year = 0; year < InNbYears; ++year)
	{
		for (int timeOfDayIndex = 0; timeOfDayIndex < 4; ++timeOfDayIndex)
		{
			Progression[timeOfDayIndex] = YS::RULER_LUCIDITY_PROGRESSION + FMath::FRandRange(-YS::RULER_LUCIDITY_PROGRESSION_DELTA, +YS::RULER_LUCIDITY_PROGRESSION_DELTA);
		}
		Progress(Progression);
	}

}

void FYSRulerData::Progress(const TArray<double>& InProgression)
{
	for (int timeOfDayIndex = 0; timeOfDayIndex < 4; ++timeOfDayIndex)
	{
		this->Lucidity[timeOfDayIndex] = this->Lucidity[timeOfDayIndex] + InProgression[timeOfDayIndex];
	}
}

FString FYSRulerData::GetLucidityText(int32 InPeriod) const
{
	if (Lucidity[InPeriod] > 0.55)
	{
		return TEXT("Wonderfull day !");
	}
	if (Lucidity[InPeriod] > 0.40)
	{
		return TEXT("Quite cosy today");
	}
	if (Lucidity[InPeriod] > 0.30)
	{
		return TEXT("A monday");
	}
	return TEXT("Life is pain");
}

FYSRulerData FYSRulerData::AutoGenerateRuler()
{
	TArray<double> Lucidity = TArray<double>();
	Lucidity.AddDefaulted(4);
	for (int timeOfDayIndex = 0; timeOfDayIndex < 4; ++timeOfDayIndex)
	{
		Lucidity[timeOfDayIndex] = YS::RULER_START_LUCIDITY[timeOfDayIndex] + FMath::FRandRange(-YS::RULER_START_LUCIDITY_DELTA[timeOfDayIndex], +YS::RULER_START_LUCIDITY_DELTA[timeOfDayIndex]);
	}
	return NewRuler(YS::RandomRulerName(), Lucidity);
}

FYSRulerData FYSRulerData::NewRuler(const FString& Name, const TArray<double>& InLucidity)
{
	FYSRulerData Ruler = FYSRulerData();
	Ruler.Name = Name;
	Ruler.Lucidity = InLucidity;
	return Ruler;
}
