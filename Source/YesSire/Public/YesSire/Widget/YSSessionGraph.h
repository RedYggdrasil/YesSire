// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "YSSessionGraph.generated.h"

/**
 * 
 */
UCLASS()
class YESSIRE_API UYSSessionGraph : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(meta = (BindWidget))
	class UYSBackgroundGraph* BW_BackgroundPE;
	UPROPERTY(meta = (BindWidget))
	class UYSSplineGraph* BW_TargetPE;
	UPROPERTY(meta = (BindWidget))
	class UYSSplineGraph* BW_ActualPE;
public:
	UFUNCTION(BlueprintCallable)
	void RedrawGraph(const struct FYSPEData& InGameState);
};
