// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "TankMovementComponent.h"

void UTankMovementComponent::Initialise(UTankTrack* leftTrackToSet, UTankTrack* rightTrackToSet) {
	if (!leftTrackToSet || !rightTrackToSet) { return; }

	leftTrack = leftTrackToSet;
	rightTrack = rightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float throwValue) {
	UE_LOG(LogTemp, Warning, TEXT("intendMoveForward called with throw : %f"), throwValue);

	leftTrack->setThrottle(throwValue);
	rightTrack->setThrottle(throwValue);
}