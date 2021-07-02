// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"

void UTankBarrel::Elevate(float relativeSpeed) {

	relativeSpeed = FMath::Clamp<float>(relativeSpeed, -1, 1);

	// move the barrel the right amount this frame

	//given the max elevation speed and frame time

	auto elevationChange = relativeSpeed * maxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto rawNewElevation = GetRelativeRotation().Pitch + elevationChange;

	auto elevation = FMath::Clamp<float>(rawNewElevation, minElevationDegrees, maxElevationDegrees);

	SetRelativeRotation(FRotator(elevation, 0, 0));
}