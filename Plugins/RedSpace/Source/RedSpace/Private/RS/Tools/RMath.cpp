// Fill out your copyright notice in the Description page of Project Settings.

#include "RS/Tools/RMath.h"
#include "RS/RS.h"

bool RMath::ClosestPointsOnTwoLines(/*out*/FVector3d& closestPointLine1, /*out*/FVector3d& closestPointLine2, const FVector3d& linePoint1, const FVector3d& lineVec1, const FVector3d& linePoint2, const FVector3d& lineVec2)
{
	closestPointLine1 = FVector3d::Zero();
	closestPointLine2 = FVector3d::Zero();

	float a = FVector3d::DotProduct(lineVec1, lineVec1);
	float b = FVector3d::DotProduct(lineVec1, lineVec2);
	float e = FVector3d::DotProduct(lineVec2, lineVec2);

	float d = a * e - b * b;

	//lines are not parallel
	if (d != 0.0f)
	{

		FVector3d r = linePoint1 - linePoint2;
		float c = FVector3d::DotProduct(lineVec1, r);
		float f = FVector3d::DotProduct(lineVec2, r);

		float s = (b * f - c * e) / d;
		float t = (a * f - c * b) / d;

		closestPointLine1 = linePoint1 + lineVec1 * s;
		closestPointLine2 = linePoint2 + lineVec2 * t;

		return true;
	}

	else
	{
		return false;
	}
}

FVector2d RMath::Vector2PerpeicularClockwise(const FVector2d& vector)
{
	return FVector2d(vector.Y, -vector.X);
}

FVector2d RMath::Vector2PerpeicularCounterClockwise(const FVector2d& vector)
{
	return FVector2d(-vector.Y, vector.X);
}

int32 RMath::WeightedDecision(const TArray<double>& InWeights)
{
	double total = 0.;
	for (double d : InWeights)
	{
		total += d;
	}
	int32 c = InWeights.Num();
	double result = FMath::RandRange(0., total);
	{
		for (int32 i = 0; i < c; ++i)
		{
			result -= InWeights[i];
			if (result <= DBL_EPSILON)
			{
				return i;
			}
		}
	}
	UE_LOG(LogTemp, Warning, TEXT(L_PATH "Unexpected rest in weighted decision ! %lf"), result);
	return c - 1;
}

int32 RMath::WeightedDecision(const TArray<float>& InWeights)
{
	float total = 0.;
	for (float d : InWeights)
	{
		total += d;
	}
	int32 c = InWeights.Num();
	float result = FMath::RandRange(0.f, total);
	{
		for (int32 i = 0; i < c; ++i)
		{
			result -= InWeights[i];
			if (result <= FLT_EPSILON)
			{
				return i;
			}
		}
	}
	UE_LOG(LogTemp, Warning, TEXT(L_PATH "Unexpected rest in weighted decision ! %f"), result);
	return c - 1;
}


int32 RMath::WeightedDecision(const TArray<int32>& InWeights)
{
	int32 total = 0.;
	for (int32 i : InWeights)
	{
		total += i;
	}
	int32 c = InWeights.Num();
	int32 result = FMath::RandRange(0, total);
	{
		for (int32 i = 0; i < c; ++i)
		{
			result -= InWeights[i];
			if (result <= 0)
			{
				return i;
			}
		}
	}
	UE_LOG(LogTemp, Warning, TEXT(L_PATH "Unexpected rest in weighted decision ! %d"), result);
	return c - 1;
}