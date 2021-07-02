// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::AimAt(FVector hitLocation, float launchSpeed) {
	if (!barrel) { return; }
	FVector launchVelocityOUT;
	FVector startLocation = barrel->GetSocketLocation(FName("Projectile"));

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		launchVelocityOUT,
		startLocation,
		hitLocation,
		launchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	//calc. launchVelocityOUT;
	if (bHaveAimSolution) {
		auto aimDirection = launchVelocityOUT.GetSafeNormal();

		MoveBarrelTowards(aimDirection);

		UE_LOG(LogTemp, Warning, TEXT("Aiming at: %s"), *(aimDirection.ToString()));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT(" No bHaveAimSolution found"));
	}

	return;
}

void UTankAimingComponent::MoveBarrelTowards(FVector aimDirection) {
	// calc diff b/w current barrel rotation and aim direction
	auto barrelRotation = barrel->GetForwardVector().Rotation();
	auto aimAtRotation = aimDirection.Rotation();
	auto deltaRotation = aimAtRotation - barrelRotation;

	barrel->Elevate(deltaRotation.Pitch);
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* barrelToSet) {
	barrel = barrelToSet;
}

