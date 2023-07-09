// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "YSSplineGraph.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, ClassGroup = "Design")
class YESSIRE_API UYSSplineGraph : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, Category = "Design")
	FLinearColor Tint = FLinearColor::White;
	UPROPERTY(EditAnywhere, Category = "Design")
	double Thickness = 1.;
	UPROPERTY(EditAnywhere, Category = "Design")
	FVector2D GraphScale = FVector2D(100., 100.);
	UPROPERTY(EditAnywhere, Category = "Design")
	FVector2D PointCorrection = FVector2D(0., 0.);
	UPROPERTY(EditAnywhere, Category = "Design")
	TArray<FVector2D> Points;

public:
	UFUNCTION(BlueprintCallable)
	void SetSpline(const FVector2D& InGraphScale, const TArray<FVector2D>& InPoints, const FLinearColor& InTint = FLinearColor::White, double InThickness = 1.);

	UFUNCTION(BlueprintCallable)
	void SetGraphScale(const FVector2D& InGraphScale) { GraphScale = InGraphScale; }

	UFUNCTION(BlueprintCallable)
	void SetPointCorrection(const FVector2D& InPointCorrection) { PointCorrection = InPointCorrection; }

	UFUNCTION(BlueprintCallable)
	void SetPoints(const TArray<FVector2D>& InPoints) { Points = InPoints; }

	UFUNCTION(BlueprintCallable)
	void SetTint(const FLinearColor& InTint) { Tint = InTint; }

	UFUNCTION(BlueprintCallable)
	void SetThickness(double InThickness) { Thickness = InThickness; }
protected:
	virtual int32 NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;

protected:
	static bool NormalizePoints(const FVector2D& InDimension, const FVector2D& InCorrection, const TArray<FVector2D>& InPoints, TArray<FVector2D>& OutNormalized);
};
