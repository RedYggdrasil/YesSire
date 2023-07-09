// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "YesSire/Defines/YSCardActionType.h"
#include "YSCardManager.generated.h"

/**
 * 
 */
UCLASS()
class YESSIRE_API UYSCardManager : public UObject
{
	GENERATED_BODY()
protected:
	UPROPERTY(Transient)
	class AYSGameState* GameState;
public:
	UFUNCTION(BlueprintCallable, blueprintPure)
	UYSCardManager* InitUObj(AYSGameState* InGameState);

	UFUNCTION(BlueprintCallable, blueprintPure)
	TArray<struct FYSCardData> CreateDeck() const;

	UFUNCTION(BlueprintCallable, blueprintPure)
	FYSCardData CreateCard() const;

	UFUNCTION(BlueprintCallable)
	void ApplyCardAction(EYSCardActionType EInCardActionType, int32 InCardIndex);
};
