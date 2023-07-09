// Fill out your copyright notice in the Description page of Project Settings.


#include "YesSire/GameplayFramework/YSPlayerController.h"
#include "RS/RS.h"
#include "YesSire/Widget/YSMainScreen.h"
#include "YesSire/Data/YSOptionData.h"

UYSMainScreen* AYSPlayerController::SetupScreen(const TSubclassOf<UYSMainScreen>& ScreenClass)
{
	FInputModeGameAndUI InputMode = FInputModeGameAndUI();
	InputMode.SetHideCursorDuringCapture(false);
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	this->SetShowMouseCursor(true);
	this->SetInputMode(InputMode);

	if (IsValid(Screen))
	{
		UE_LOG(LogTemp, Warning, TEXT(L_PATH "Already a screen present, resetting it !"));
		Screen->RemoveFromParent();
	}
	Screen = Cast<UYSMainScreen>(CreateWidget(this, ScreenClass));
	if (!IsValid(Screen))
	{
		UE_LOG(LogTemp, Error, TEXT(L_PATH "Failed to Spawn a screen !"));
		return nullptr;
	}

	Screen->AddToViewport();
	return Screen;
}

void AYSPlayerController::ApplyOptions(const FYSOptionData& InOptionData)
{
}

void AYSPlayerController::UpdateScreen(const FYSPEData& InPEData)
{
	Screen->UpdateGameState(InPEData);
}

void AYSPlayerController::AnimateCardDiscard(int32 InCardIndex, double InCardAnimTime, bool bInCardDiscarded, const TMap<EYSResourceType, int32>& ResourceChanged)
{
}
