// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "YesSire/Data/YSPEData.h"
#include "YesSire/Defines/YSResourceType.h"
#include "YesSire/Defines/YSRuleEndType.h"
#include "YSGameState.generated.h"

/**
 * 
 */

UENUM()
enum class EGameStateAnimType : uint8
{
	DrawCard = 0,
	PlayCard = 1,
	DiscardCard = 2,
	RuleEnd = 3,
	PlanEnd = 4,
	SessionEnd = 5,
	None = 6,
	COUNT = 7
};

UCLASS()
class YESSIRE_API AYSGameState : public AGameStateBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(Transient)
	EGameStateAnimType CurrentAnimation = EGameStateAnimType::None;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Design")
	TSubclassOf<class UYSMainScreen> ScreenClass;

protected:
	UPROPERTY(Transient)
	class UYSSaveGame* CurrentSave = nullptr;

	UPROPERTY(Transient)
	class AYSPlayerController* Mpc = nullptr;

	UPROPERTY(Transient)
	class UYSCardManager* CardManager = nullptr;

	FTimerHandle TimerHandle;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Design|Game")
	FYSPEData PEData;

public:
	const FYSPEData& GetPEData() const { return PEData; };

	UFUNCTION(BlueprintCallable)
	FYSPEData& GetPEData() { return PEData; };

	UFUNCTION(BlueprintCallable, BlueprintPure)
	UYSCardManager* GetCardManager() const { return CardManager; }

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void LoadSession(const FYSPEData& InPEData);

	UFUNCTION(BlueprintCallable)
	void StartNewSession();
public:
	UFUNCTION(BlueprintCallable)
	void StartEndTurn();
	UFUNCTION(BlueprintCallable)
	void EndTurnProcedure();

	UFUNCTION(BlueprintCallable)
	void PrepareNextTurn(bool bSkipSave = false);
	UFUNCTION(BlueprintCallable)
	void StartNextTurn();

	UFUNCTION(BlueprintCallable)
	void ApplyRuleEnd(EYSRuleEndType EInRuleEndType, EYSResourceType EInPotencialAssociatedResource = EYSResourceType::COUNT);
	
	UFUNCTION(BlueprintCallable)
	void ApplySelectedCard(int32 InSelectedCardIndex);

	UFUNCTION(BlueprintCallable)
	void ApplySkipButton();

	UFUNCTION(BlueprintCallable)
	void OnAppliedSelectedCard();

	UFUNCTION(BlueprintCallable)
	void ApplyPeriodEnd();

	UFUNCTION(BlueprintCallable)
	void ApplyPlanEnd();

	UFUNCTION(BlueprintCallable)
	void ApplySessionEnd();

	UFUNCTION(BlueprintCallable)
	void OnCardActionApplied(int32 InCardIndex, double InCardAnimTime, bool bInCardDiscarded, const TMap<EYSResourceType, int32>& ResourceChanged);

	UFUNCTION()
	void OnAnimatedRuleEnd();
	UFUNCTION()
	void OnAnimatedPlanEnd();
protected:

	UFUNCTION(BlueprintCallable)
	void SetAnimState(EGameStateAnimType InAnimState);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	UYSMainScreen* Screen() const;

	UFUNCTION()
	void ContinueProcedureAfterAnimation();
};
