// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "YesSire/Data/YSUserData.h"
#include "YSSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class YESSIRE_API UYSSaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	static const FString SAVE_SLOT;
protected:
	UPROPERTY(VisibleAnywhere, Category = Design)
	int32 UserIndex = 0;
	UPROPERTY(EditAnywhere, Category = "Save")
	FYSUserData UserData;
public:
	UFUNCTION(BlueprintCallable)
	void SetUserIndex(int32 InUserIndex) { UserIndex = InUserIndex; }

	UFUNCTION(BlueprintCallable)
	FYSUserData& GetUserData() { return UserData; }
	const FYSUserData& GetUserData() const { return UserData; }

	UFUNCTION(BlueprintCallable)
	bool CommitSave();
public:
	static UYSSaveGame* LoadSave(int32 InIndex = 0);
	static void DeleteSave(int32 InIndex = 0);
};
