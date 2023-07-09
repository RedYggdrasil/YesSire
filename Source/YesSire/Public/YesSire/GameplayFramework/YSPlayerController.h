// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "YSPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class YESSIRE_API AYSPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	UPROPERTY(Transient)
	UYSMainScreen* Screen = nullptr;

public:
	UFUNCTION(BlueprintCallable)
	UYSMainScreen* SetupScreen(const TSubclassOf<class UYSMainScreen>& ScreenClass);

	UFUNCTION(BlueprintCallable)
	void ApplyOptions(const struct FYSOptionData& InOptionData);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	UYSMainScreen* GetScreen() const { return Screen; }

	UFUNCTION(BlueprintCallable)
	void UpdateScreen(const FYSPEData& InPEData);

	UFUNCTION(BlueprintCallable)
	void AnimateCardDiscard(int32 InCardIndex, double InCardAnimTime, bool bInCardDiscarded, const TMap<EYSResourceType, int32>& ResourceChanged);

};
