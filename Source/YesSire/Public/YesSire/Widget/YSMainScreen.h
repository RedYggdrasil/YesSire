// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "YesSire/Data/YSPEData.h"
#include "YSMainScreen.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, ClassGroup = "Design")
class YESSIRE_API UYSMainScreen : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(meta = (BindWidget))
	class UYSSessionGraph* BW_SessionGraph;

	UPROPERTY(meta = (BindWidget))
	class UButton* BW_SkipButton;
	UPROPERTY(meta = (BindWidget))
	class UImage* BW_KingYes;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* BW_KingState;
	UPROPERTY(meta = (BindWidget))
	class UImage* BW_KingNo;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* BW_SkipButtonText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* BW_NBCofferText;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* BW_NBSocietyText;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* BW_NBIdeologyText;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* BW_NBMillitaryText;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* BW_NBTechnologyText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* BW_RulerNameText;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* BW_CounselorNameText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* BW_NBHighDeltaText;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* BW_NBPlanResetText;
	UPROPERTY(meta = (BindWidget))
	class UYSHandWidget* BW_HandWidget;


	UPROPERTY(meta = (BindWidget))
	UTextBlock* BW_YearText;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* BW_EndYearText;


	UPROPERTY(meta = (BindWidget))
	UTextBlock* BW_SeasonText;

	UPROPERTY(meta = (BindWidget))
	class UYSGameOver* BW_GameOver;

protected:
	virtual void NativeOnInitialized() override;
public:
	void UpdateGameState(const FYSPEData& InGameState);

	void AnimateKingDied();
	void AnimateCounselorDied();
	void AnimateKingDecision(bool bInDecision);
	void ShowGameOver(bool bSucess);
protected:
	UFUNCTION()
	void OnSkipClicked();

	static FLinearColor ValueToColor(int32 InValue);
};
