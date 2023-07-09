// Fill out your copyright notice in the Description page of Project Settings.


#include "YesSire/Widget/YSBackgroundGraph.h"
#include "RS/RS.h"
#include "YesSire/Style/YSStyleData.h"

#define SLoc(Val) (((Val) * Size) + InnerMargin.GetTopLeft())
void UYSBackgroundGraph::SetGraphDatas(const FVector2D& InGraphZero, const FVector2D& InGraphUnits, const FLinearColor& InTint, double InThickness)
{
	GraphZero = InGraphZero;
	GraphUnits = InGraphUnits;
	SetTint(InTint);
	SetThickness(InThickness);
}

int32 UYSBackgroundGraph::NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	int32 MaxLayer = Super::NativePaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);

	FVector2D Size = AllottedGeometry.GetLocalSize();
	Size = FVector2D(Size.X - InnerMargin.GetTotalSpaceAlong<EOrientation::Orient_Horizontal>(), Size.Y - InnerMargin.GetTotalSpaceAlong<EOrientation::Orient_Vertical>());
	
	int32 MaxX = GraphUnits.X;
	int32 MaxY = GraphUnits.Y;

	//UE_LOG(LogTemp, Display, TEXT(L_PATH "MaxX %d"), MaxX);
	//UE_LOG(LogTemp, Display, TEXT(L_PATH "MaxY %d"), MaxY);
	//UE_LOG(LogTemp, Display, TEXT("Size %s"), *Size.ToString());
	FLinearColor TintIntencity;
	if (bParentEnabled && MaxX > 0 && MaxY > 0)
	{
		++MaxLayer;
		for (int x = 0; x < MaxX; ++x)
		{
			TintIntencity = (x % 10 == 0) ? Tint : YSStyleT::ComposeAlpha(Tint, 0.1);
			double normX = (double)x / (double)MaxX;
			//UE_LOG(LogTemp, Display, TEXT("normX %d | VecX %s"), normX, *SLoc(FVector2D(normX, 0.)).ToString());
			FSlateDrawElement::MakeLines
			(
				OutDrawElements, MaxLayer, AllottedGeometry.ToPaintGeometry(),
				TArray<FVector2D> {SLoc(FVector2D(normX, 0.)), SLoc(FVector2D(normX, 1.))},
				ESlateDrawEffect::None, TintIntencity, true, Thickness
			);
		}
		for (int y = 0; y < MaxY; ++y)
		{
			TintIntencity = (y % 10 == 0) ? Tint : YSStyleT::ComposeAlpha(Tint, 0.1);
			double normY = (double)y / (double)MaxY;
			FSlateDrawElement::MakeLines
			(
				OutDrawElements, MaxLayer, AllottedGeometry.ToPaintGeometry(),
				TArray<FVector2D> {SLoc(FVector2D(0., normY)), SLoc(FVector2D(1., normY)) },
				ESlateDrawEffect::None, TintIntencity, true, Thickness
			);
		}
	}
	return MaxLayer;
}

//bool UYSBackgroundGraph::NormalizePoints(const FVector2D & InDimension, const FVector2D & InCorrection, const TArray<FVector2D>&InPoints, TArray<FVector2D>&OutNormalized)
//{
//	OutNormalized.Empty(InPoints.Num());
//	if (InDimension.X <= 0 || InDimension.Y <= 0)
//	{
//		OutNormalized.AddZeroed(InPoints.Num());
//		return false;
//	}
//	for (int i = 0; i < InPoints.Num(); ++i)
//	{
//		FVector2D val = ((InPoints[i] + InCorrection) / InDimension);
//		val.Y = 1 - val.Y;
//		OutNormalized.Add(val);
//	}
//	return true;
//}
#undef SLoc