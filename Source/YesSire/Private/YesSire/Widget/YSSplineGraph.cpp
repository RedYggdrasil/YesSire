// Fill out your copyright notice in the Description page of Project Settings.


#include "YesSire/Widget/YSSplineGraph.h"
//#include "Engine/GameViewportClient.h"
//#include "Brushes/SlateNoResource.h"
//#include "Rendering/DrawElements.h"
//#include "Styling/SlateTypes.h"
//#include "Styling/CoreStyle.h"
//#include "Styling/UMGCoreStyle.h"
//#include "Framework/Application/SlateApplication.h"
#include "RS/RS.h"

#define PLoc(Val) AllottedGeometry.GetLocalPositionAtCoordinates(Val)
#define SLoc(Val) ((Val) * Size)

void UYSSplineGraph::SetSpline(const FVector2D& InGraphScale, const TArray<FVector2D>& InPoints, const FLinearColor& InTint, double InThickness)
{
	SetGraphScale(InGraphScale);
	SetPoints(InPoints);
	SetTint(InTint);
	SetThickness(InThickness);
}


int32 UYSSplineGraph::NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	int32 MaxLayer = Super::NativePaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);
	
	FGeometry gem = GetCachedGeometry();
	//UE_LOG(LogTemp, Display, TEXT("AllottedGeometry : [%s]"), *AllottedGeometry.ToString());
	//UE_LOG(LogTemp, Display, TEXT("Gem : [%s]"), *gem.ToString());
	//UE_LOG(LogTemp, Display, TEXT("Points.Num() : [%d]"), Points.Num());
	TArray<FVector2D> norms;
	int pCount = Points.Num();
	int pCM = pCount - 1;
	int pCM2 = pCount - 2;

	FVector2D Size = AllottedGeometry.GetLocalSize();

	//FSlateDrawElement::MakeSpline
	//(
	//	OutDrawElements, MaxLayer, AllottedGeometry.ToPaintGeometry(),
	//	SLoc(FVector2D(0, 0)),
	//	SLoc(FVector2D(1, 1)),
	//	SLoc(FVector2D(1, 1)),
	//	SLoc(FVector2D(1, 1)),
	//	Thickness, ESlateDrawEffect::None, Tint
	//);

	if (bParentEnabled && pCount > 1 && ThisClass::NormalizePoints(this->GraphScale, this->PointCorrection, this->Points, norms))
	{
		++MaxLayer;
		FVector2D LastEndDir;
		FVector2D NextEndDir;
		if (pCount == 2)
		{
			LastEndDir = norms[1] - norms[0];
		}
		else
		{
			LastEndDir = ((norms[2] - norms[0]) / 2.);
			//endDir0 = norms[1] - n;
		}
		FSlateDrawElement::MakeSpline
		(
			OutDrawElements, MaxLayer, AllottedGeometry.ToPaintGeometry(),
			SLoc(norms[0]),
			SLoc(norms[1] - norms[0]),
			SLoc(norms[1]),
			SLoc(LastEndDir),
			Thickness, ESlateDrawEffect::None, Tint
		);
		for (int i = 1; i < pCM2; ++i)
		{
			NextEndDir = ((norms[i + 2] - norms[i]) / 2.);
			FSlateDrawElement::MakeSpline
			(
				OutDrawElements, MaxLayer, AllottedGeometry.ToPaintGeometry(),
				SLoc(norms[i]),
				SLoc(LastEndDir),
				SLoc(norms[i+1]),
				SLoc(NextEndDir),
				Thickness, ESlateDrawEffect::None, Tint
			);
			LastEndDir = NextEndDir;
		}
		if (pCount > 2)
		{
			FSlateDrawElement::MakeSpline
			(
				OutDrawElements, MaxLayer, AllottedGeometry.ToPaintGeometry(),
				SLoc(norms[pCM2]),
				SLoc(LastEndDir),
				SLoc(norms[pCM]),
				SLoc(norms[pCM] - norms[pCM2]),
				Thickness, ESlateDrawEffect::None, Tint
			);
		}
	}
	return MaxLayer;
}

bool UYSSplineGraph::NormalizePoints(const FVector2D& InDimension, const FVector2D& InCorrection, const TArray<FVector2D>& InPoints, TArray<FVector2D>& OutNormalized)
{
	OutNormalized.Empty(InPoints.Num());
	if (InDimension.X <= 0 || InDimension.Y <= 0)
	{
		OutNormalized.AddZeroed(InPoints.Num());
		return false;
	}
	for (int i = 0; i < InPoints.Num(); ++i)
	{
		FVector2D val = ((InPoints[i] + InCorrection) / InDimension);
		val.Y = 1 - val.Y;
		OutNormalized.Add(val);
	}
	return true;
}
#undef PLoc
#undef SLoc