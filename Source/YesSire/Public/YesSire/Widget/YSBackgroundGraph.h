// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "YSBackgroundGraph.generated.h"

/**
 * 
 */
UCLASS()
class YESSIRE_API UYSBackgroundGraph : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, Category = "Design")
	FLinearColor Tint = FLinearColor::White;
	UPROPERTY(EditAnywhere, Category = "Design")
	double Thickness = 1.;

	UPROPERTY(EditAnywhere, Category = "Design")
	FMargin InnerMargin;

	UPROPERTY(EditAnywhere, Category = "Design")
	FVector2D GraphZero = FVector2D(0., 0.);
	UPROPERTY(EditAnywhere, Category = "Design")
	FVector2D GraphUnits = FVector2D(100., 100.);
public:
	UFUNCTION(BlueprintCallable)
	void SetGraphDatas(const FVector2D& InGraphZero, const FVector2D& InGraphUnits, const FLinearColor& InTint = FLinearColor::White, double InThickness = 1.);

	UFUNCTION(BlueprintCallable)
	void SetTint(const FLinearColor& InTint) { Tint = InTint; }

	UFUNCTION(BlueprintCallable)
	void SetThickness(double InThickness) { Thickness = InThickness; }
protected:
	virtual int32 NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;

protected:
//	static bool NormalizePoints(const FVector2D& InDimension, const TArray<FVector2D>& InPoints, TArray<FVector2D>& OutNormalized);
};
