// Fill out your copyright notice in the Description page of Project Settings.


#include "YesSire/Save/YSSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "RS/RS.h"

const FString UYSSaveGame::SAVE_SLOT = FString("DefaultSaveSlot");
bool UYSSaveGame::CommitSave()
{
	if (UGameplayStatics::SaveGameToSlot(this, UYSSaveGame::SAVE_SLOT, UserIndex))
	{
		return true;
	}
	return false;
}

UYSSaveGame* UYSSaveGame::LoadSave(int32 InIndex)
{
	UYSSaveGame* saveData = nullptr;
	if (IsValid(saveData = Cast<UYSSaveGame>(UGameplayStatics::LoadGameFromSlot(UYSSaveGame::SAVE_SLOT, InIndex))))
	{

	}
	else if (IsValid(saveData = Cast<UYSSaveGame>(UGameplayStatics::CreateSaveGameObject(UYSSaveGame::StaticClass()))))
	{
		UE_LOG(LogTemp, Warning, TEXT(L_PATH "Creating New UYSSaveGame"));
	}

	if (IsValid(saveData))
	{
		saveData->SetUserIndex(InIndex);
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT(L_PATH "Failed to load or create UYSSaveGame !"));
	}
	return saveData;
}

void UYSSaveGame::DeleteSave(int32 InIndex)
{
	UGameplayStatics::DeleteGameInSlot(UYSSaveGame::SAVE_SLOT, InIndex);
}
