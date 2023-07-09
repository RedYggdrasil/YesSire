// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "YSGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class YESSIRE_API UYSGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = Design)
	class UYSStyleDA* DefaultStypeDA;

public:
	virtual void Init() override;
	virtual void Shutdown() override;

	void InternalInitializeGameInstance(bool bInInitialInit);

	UFUNCTION(BlueprintCallable)
	void ResetApplication();
};
