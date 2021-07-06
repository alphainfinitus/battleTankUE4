// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"

void UTankTrack::setThrottle(float throttle) {
	UE_LOG(LogTemp, Warning, TEXT("Setting throttle"));

	//TODO clamp throttle values

	auto forceApplied = GetForwardVector() * throttle * maxDrivingForce;

	auto forceLocation = GetComponentLocation();

	auto tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	tankRoot->AddForceAtLocation(forceApplied, forceLocation);
}