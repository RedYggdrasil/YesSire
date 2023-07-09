// Fill out your copyright notice in the Description page of Project Settings.


#include "YesSire/Widget/YSGameOver.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "YesSire/GameplayFramework/YSGameInstance.h"



void UYSGameOver::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	BW_RestartButton->OnClicked.AddUniqueDynamic(this, &ThisClass::OnRestartButton);
}

void UYSGameOver::OnRestartButton()
{
	Cast<UYSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->ResetApplication();
}
