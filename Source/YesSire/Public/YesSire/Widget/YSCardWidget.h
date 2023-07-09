// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "YSCardWidget.generated.h"

/**
 * 
 */
UCLASS()
class YESSIRE_API UYSCardWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(Transient)
	int32 CardIndex = 0;
	UPROPERTY(Transient)
	class UYSHandWidget* HandWidget = nullptr;
protected:
	UPROPERTY(meta = (BindWidget))
	class UButton* BW_CardButton;
	UPROPERTY(meta = (BindWidget))
	class UYSValueSummaryWidget* BW_OkSummary;
	UPROPERTY(meta = (BindWidget))
	class UYSValueSummaryWidget* BW_NoSummary;
	UPROPERTY(meta = (BindWidget))
	class UYSValueSummaryWidget* BW_DiscardSummary;
protected:
	virtual void NativeOnInitialized() override;
public:
	UYSCardWidget* InitUObj(const struct FYSCardData& InCardData, UYSHandWidget* InHandWidget, int32 InCardIndex);
protected:
	UFUNCTION()
	void OnCardClicked();
};
