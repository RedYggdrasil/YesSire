// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "YesSire/Style/YSStyleData.h"
#include "YSStyleDA.generated.h"

/**
 * 
 */
UCLASS()
class YESSIRE_API UYSStyleDA : public UDataAsset
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Design")
	FYSStyleData StypeData;
public:
	//UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE const FYSStyleData& GetStyle() const { return StypeData; }
	
};
