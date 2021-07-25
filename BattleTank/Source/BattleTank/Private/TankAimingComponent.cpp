// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "Projectile.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::BeginPlay() {
	Super::BeginPlay();

	//so that first fire is after initial reload
	lastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	bool bIsReloading = (FPlatformTime::Seconds() - lastFireTime) < reloadTimeInSeconds;

	if (ammoCount<=0) {
		firingState = EFiringState::OutOfAmmo;
	}
	else if (bIsReloading) {
		firingState = EFiringState::Reloading; 
	} 
	else if (IsBarrelMoving()) {
		firingState = EFiringState::Aiming;
	}
	else {
		firingState = EFiringState::Ready;
	}
}

void UTankAimingComponent::Initialise(UTankBarrel* barrelToSet, UTankTurret* turretToSet) {
	if (!ensure(barrelToSet && turretToSet)) { return; }

	barrel = barrelToSet;
	turret = turretToSet;
}

bool UTankAimingComponent::IsBarrelMoving() {
	if (!ensure(barrel)) { return false; }

	auto barrelForwardVector = barrel->GetForwardVector();
	return !barrelForwardVector.Equals(aimDirection, 0.01);
}

void UTankAimingComponent::AimAt(FVector hitLocation) {
	if (!ensure(barrel)) { return; }

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
		aimDirection = launchVelocityOUT.GetSafeNormal();

		MoveBarrelTowardsAimDirection();
	}

	return;
}

void UTankAimingComponent::MoveBarrelTowardsAimDirection() {

	if (!ensure(barrel) || !ensure(turret)) { return; }

	// calc diff b/w current barrel rotation and aim direction
	auto barrelRotation = barrel->GetForwardVector().Rotation();
	auto aimAtRotation = aimDirection.Rotation();
	auto deltaRotation = aimAtRotation - barrelRotation;

	barrel->Elevate(deltaRotation.Pitch);

	//to always yaw the shortest distance (angle)
	if (FMath::Abs(deltaRotation.Yaw) < 180) {
		turret->Rotate(deltaRotation.Yaw);
	}
	else {
		turret->Rotate(-deltaRotation.Yaw);

	}
}

void UTankAimingComponent::Fire() {

	if (firingState == EFiringState::Reloading || firingState == EFiringState::OutOfAmmo) { return; }
	//spawn a projectile at barrel's socket location

	if (!ensure(barrel && projectileBlueprint)) { return; }

	auto projectile = GetWorld()->SpawnActor<AProjectile>(
		projectileBlueprint,
		barrel->GetSocketLocation(FName("Projectile")),
		barrel->GetSocketRotation(FName("Projectile"))
		);

	projectile->launchProjectile(launchSpeed);

	ammoCount--;

	lastFireTime = FPlatformTime::Seconds();
}


EFiringState UTankAimingComponent::GetFiringState() const {
	return firingState;
}

int32 UTankAimingComponent::GetAmmoCount() const {
	return ammoCount;
}