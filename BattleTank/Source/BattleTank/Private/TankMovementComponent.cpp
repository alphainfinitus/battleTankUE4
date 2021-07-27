// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "TankMovementComponent.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include "Sound/SoundCue.h"

UTankMovementComponent::UTankMovementComponent() {

	static ConstructorHelpers::FObjectFinder<USoundCue> tankMovingSound(TEXT("/Game/Audio/old_tank_moving_Cue.old_tank_moving_Cue"));
	tankMovingSoundCue = tankMovingSound.Object;
}

void UTankMovementComponent::Initialise(UTankTrack* leftTrackToSet, UTankTrack* rightTrackToSet) {
	if (!ensure(leftTrackToSet && rightTrackToSet)) { return; }

	leftTrack = leftTrackToSet;
	rightTrack = rightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float throwValue) {
	/*
	
	UAudioComponent* AudioComponent = UGameplayStatics::SpawnSoundAtLocation(
		this,
		tankMovingSoundCue,
		GetOwner()->GetActorLocation(),
		FRotator::ZeroRotator, 1, 1, 0.0f, nullptr, nullptr, true
	);

	*/

	leftTrack->setThrottle(throwValue);
	rightTrack->setThrottle(throwValue);
}

//negative values make it turn left
void UTankMovementComponent::IntendTurnRight(float throwValue) {
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
}