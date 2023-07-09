// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "YSHandWidget.generated.h"

/**
 * 
 */
UCLASS()
class YESSIRE_API UYSHandWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Design")
	TSubclassOf<class UYSCardWidget> CardWidgetClass;
protected:
	UPROPERTY(meta = (BindWidget))
	class UButton* BW_ToggleViewButton;
	UPROPERTY(meta = (BindWidget))
	class UWrapBox* BW_HandTile;
	
protected:
	virtual void NativeOnInitialized() override;
public:
	UFUNCTION(BlueprintCallable)
	void RedrawHand(const struct FYSRuleStateData& RuleData);

	UFUNCTION(BlueprintCallable)
	void AnimateCard(int32 InCardIndex, double InTime);
protected:
	UFUNCTION()
	void OnToggleVisibility();

protected:
	UFUNCTION()
	void OnCardClicked(int32 InCardIndex);
	friend class UYSCardWidget;
};
