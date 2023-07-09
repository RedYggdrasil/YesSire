// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
static class REDSPACE_API RMath
{
public:
	/// <summary>
	/// Two non-parallel lines which may or may not touch each other have a point on each line which are closest
	///	to each other. This function finds those two points. If the lines are not parallel, the function 
	///	outputs true, otherwise false.
	/// </summary>
	/// <param name="closestPointLine1"></param>
	/// <param name="closestPointLine2"></param>
	/// <param name="linePoint1"></param>
	/// <param name="lineVec1"></param>
	/// <param name="linePoint2"></param>
	/// <param name="lineVec2"></param>
	/// <returns></returns>
	static bool ClosestPointsOnTwoLines(/*out*/FVector3d& closestPointLine1, /*out*/FVector3d& closestPointLine2, const FVector3d& linePoint1, const FVector3d& lineVec1, const FVector3d& linePoint2, const FVector3d& lineVec2);

	static FVector2d Vector2PerpeicularClockwise(const FVector2d& vector);
	static FVector2d Vector2PerpeicularCounterClockwise(const FVector2d& vector);

	static int32 WeightedDecision(const TArray<double>& InWeights);
	static int32 WeightedDecision(const TArray<float>& InWeights);
	static int32 WeightedDecision(const TArray<int32>& InWeights);

};
