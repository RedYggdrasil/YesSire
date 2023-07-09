// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "YSGameOver.generated.h"

/**
 * 
 */
UCLASS()
class YESSIRE_API UYSGameOver : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(meta = (BindWidget))
	class UButton* BW_RestartButton;
protected:
	virtual void NativeOnInitialized() override;
protected:
	UFUNCTION()
	void OnRestartButton();
};
