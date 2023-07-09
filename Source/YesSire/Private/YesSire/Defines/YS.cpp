// Fill out your copyright notice in the Description page of Project Settings.


#include "YesSire/Defines/YS.h"
#include "RS/RS.h"


const TArray<FString> YS::RULER_NAMES =
{
	"Abdul",
	"Alexander",
	"Arthur",
	"Augustus",
	"Bismarck",
	"Catherine",
	"Constantine",
	"Cleopatra",
	"Genghis",
	"Joan",
	"Ned",
	"Pericles",
	"Qin Shi",
	"Regis",
	"Suleiman",
	"Victoria",
	"William",
	"Wu Zetian"
};

const TArray<FString> YS::COUNSELOR_NAMES =
{
	"Lillian",
	"Saskia",
	"Alyssa",
	"Matthew",
	"Madeline",
	"Evangeline",
	"Zayd",
	"Dale",
	"Marcel",
	"Dean",
	"Laila",
	"Isembard",
	"Troy",
	"Lee",
	"Ulyaa",
	"Saara",
	"Thomas",
	"Henry",
	"Florian",
	"Himma",
	"Jeelaan",
	"Xander",
	"Leon",
};


const TArray<FString> YS::YEAR_PERIOD_DISPLAY_NAMES =
{
	"Winter",
	"Spring",
	"Summer",
	"Fall"
};

FString YS::RandomRulerName()
{
	return YS::RULER_NAMES[FMath::RandRange(0, YS::RULER_NAMES.Num() - 1)];
}

FString YS::RandomCounselorName()
{
	return YS::COUNSELOR_NAMES[FMath::RandRange(0, YS::COUNSELOR_NAMES.Num() - 1)];
}
