// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "TankMovementComponent.h"

void UTankMovementComponent::Initialise(UTankTrack* leftTrackToSet, UTankTrack* rightTrackToSet) {
	if (!leftTrackToSet || !rightTrackToSet) { return; }

	leftTrack = leftTrackToSet;
	rightTrack = rightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float throwValue) {
	//TODO clamp throttle values

	leftTrack->setThrottle(throwValue);
	rightTrack->setThrottle(throwValue);
}

//negative values make it turn left
void UTankMovementComponent::IntendTurnRight(float throwValue) {
	//TODO clamp throttle values

	leftTrack->setThrottle(throwValue);
	rightTrack->setThrottle(-throwValue);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) {

	//no need to call super
	auto tankForwardDirection = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto aiForwardIntention = MoveVelocity.GetSafeNormal();

	auto forwardThrow = FVector::DotProduct(tankForwardDirection, aiForwardIntention);
	IntendMoveForward(forwardThrow);

	auto rightThrow = FVector::CrossProduct(tankForwardDirection, aiForwardIntention).Z;
	IntendTurnRight(rightThrow);

	//UE_LOG(LogTemp, Warning, TEXT("%s vectoring to %s"), *tankName, *moveVelocityString);
}