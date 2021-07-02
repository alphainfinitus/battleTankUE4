// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"

void UTankTurret::Rotate(float relativeSpeed) {

	relativeSpeed = FMath::Clamp<float>(relativeSpeed, -1, 1);

	auto rotationChange = relativeSpeed * maxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto rotation = GetRelativeRotation().Yaw + rotationChange;

	SetRelativeRotation(FRotator(0, rotation, 0));
}