// Fill out your copyright notice in the Description page of Project Settings.


#include "YesSire/Widget/YSSessionGraph.h"
#include "RS/RS.h"
#include "YesSire/Data/YSPEData.h"
#include "YesSire/Style/YSStyleData.h"
#include "YesSire/Widget/YSBackgroundGraph.h"
#include "YesSire/Widget/YSSplineGraph.h"

void UYSSessionGraph::RedrawGraph(const FYSPEData& InGameState)
{
	const FYSPEGlobalStateData& GS = InGameState.GlobalState;
	FVector2D Correction = FVector2D(-GS.StartYear, 0.);
	FVector2D FGraphDimension = FVector2D(GS.GetTotalYears(), 100.);


	BW_BackgroundPE->SetGraphDatas(FVector2D(GS.StartYear, 0.), FGraphDimension, YSStyleI.DarkActionColorA(), 0.5);

	BW_TargetPE->SetPointCorrection(Correction);
	BW_ActualPE->SetPointCorrection(Correction);


	BW_TargetPE->SetSpline(FGraphDimension, GS.TargetPE, YSStyleI.TargetLineColor, 1.);
	BW_ActualPE->SetSpline(FGraphDimension, GS.ActualPE, YSStyleI.GameLineColor, 1.);
}
