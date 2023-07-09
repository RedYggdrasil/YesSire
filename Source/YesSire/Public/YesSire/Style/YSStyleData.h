// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "YSStyleData.generated.h"

#define FAlpha(InName, InFunc) inline FLinearColor InFunc() const { return InFunc(MainBackgroundAlpha); } inline FLinearColor InFunc(double InApha) const { return ComposeAlpha(InName, InApha); }
/**
 * 
 */
USTRUCT(BlueprintType)
struct YESSIRE_API FYSStyleData
{
	GENERATED_USTRUCT_BODY()
public:
	static const FYSStyleData& Get();
public:
	static const FYSStyleData DEFAULT;
private:
	static const FYSStyleData* ActiveStyle;
	static bool bIsStypeGame;

	bool bIsDefault = false;
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Design")
	double MainBackgroundAlpha = 0.5;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Design")
	FLinearColor MainActionColor = FColor::FromHex("#F28861"); FAlpha(MainActionColor, MainActionColorA);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Design")
	FLinearColor SecondaryActionColor = FColor::FromHex("#F0BBA8"); FAlpha(SecondaryActionColor, SecondaryActionColorA);


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Design")
	FLinearColor DarkActionColor = FColor::FromHex("#6B3C2B"); FAlpha(DarkActionColor, DarkActionColorA);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Design")
	FLinearColor DarkerActionColor = FColor::FromHex("#381F16"); FAlpha(DarkerActionColor, DarkerActionColorA);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Design")
	FLinearColor LightActionColor = FColor::FromHex("#E5CCC2"); FAlpha(LightActionColor, LightActionColorA);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Design")
	FLinearColor LighterActionColor = FColor::FromHex("#E4D4CD"); FAlpha(LighterActionColor, LighterActionColorA);


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Design")
	FLinearColor MainActionBlackColor = FLinearColor(0.010417, 0.002216, 0.000597, 1.000000); FAlpha(MainActionBlackColor, MainActionBlackColorA);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Design")
	FLinearColor MainActionWhiteColor = FColor::FromHex("#F2E6E2"); FAlpha(MainActionWhiteColor, MainActionWhiteColorA);


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Design")
	FLinearColor PositiveColor = FColor::FromHex("#75F566"); FAlpha(PositiveColor, PositiveColorA);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Design")
	FLinearColor WarningColor = FColor::FromHex("#FFB65D"); FAlpha(WarningColor, WarningColorA);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Design")
	FLinearColor ErrorColor = FColor::FromHex("#F04860"); FAlpha(ErrorColor, ErrorColorA);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Design")
	FLinearColor TargetLineColor = FColor::FromHex("#05BFFA"); FAlpha(TargetLineColor, TargetLineColorA);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Design")
	FLinearColor GameLineColor = FColor::FromHex("#FACE05"); FAlpha(GameLineColor, GameLineColorA);

public:
	inline bool IsDefault() const { return bIsDefault; }
private:
	static void SetInGameStyle(const FYSStyleData& InData);
	static void ResetInGameStyle();

	static FYSStyleData CreateDefault();
public:
	FLinearColor ComposeAlphaMBG(const FLinearColor& InColor) const { return FLinearColor(InColor.R, InColor.G, InColor.B, MainBackgroundAlpha); }
	static FLinearColor ComposeAlpha(const FLinearColor& InColor, double InAlpha) { return FLinearColor(InColor.R, InColor.G, InColor.B, InAlpha); }
private:
	friend class UYSGameInstance;
};
#undef FAlpha
#define YSStyleT FYSStyleData
#define YSStyleI FYSStyleData::Get()
