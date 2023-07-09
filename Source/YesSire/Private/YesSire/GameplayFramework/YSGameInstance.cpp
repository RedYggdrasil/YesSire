// Fill out your copyright notice in the Description page of Project Settings.


#include "YesSire/GameplayFramework/YSGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "YesSire/Style/YSStyleDA.h"
#include "YesSire/Style/YSStyleData.h"

void UYSGameInstance::Init()
{
	Super::Init();
	InternalInitializeGameInstance(true);
}

void UYSGameInstance::Shutdown()
{
	if (GetWorld()->IsGameWorld())
	{
		FYSStyleData::ResetInGameStyle();
	}
	Super::Shutdown();
}

void UYSGameInstance::InternalInitializeGameInstance(bool bInInitialInit)
{
	if (GetWorld()->IsGameWorld())
	{
		FYSStyleData::SetInGameStyle(DefaultStypeDA->GetStyle());
	}
}

void UYSGameInstance::ResetApplication()
{
	UGameplayStatics::OpenLevel(GetWorld(), GetWorld()->GetFName(), true);
	InternalInitializeGameInstance(false);
}
