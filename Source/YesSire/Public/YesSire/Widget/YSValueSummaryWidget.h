// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
//#include "YesSire/Data/YSActionValuesData.h"
#include "YesSire/Defines/YSResourceType.h"
#include "YSValueSummaryWidget.generated.h"

/**
 * 
 */
UCLASS()
class YESSIRE_API UYSValueSummaryWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* BW_CofferChange;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* BW_SocietyChange;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* BW_IdeologyChange;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* BW_MillitaryChange;
public:
	UFUNCTION(BlueprintCallable)
	void AddInfo(EYSResourceType EInResourceType, int32 InValue);
protected:
	UTextBlock* GetTextBlock(EYSResourceType EInResourceType) const;
};
