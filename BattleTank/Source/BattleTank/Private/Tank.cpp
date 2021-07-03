// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//no need to protect pointer on constructor
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::AimAt(FVector hitLocation) {
	TankAimingComponent->AimAt(hitLocation, launchSpeed);
}

void ATank::Fire() {
	UE_LOG(LogTemp, Warning, TEXT("Firing"));
	if (!barrel) { return; }

	//spawn a projectile at barrel's socket location

	GetWorld()->SpawnActor<AProjectile>(
		projectileBlueprint,
		barrel->GetSocketLocation(FName("Projectile")),
		barrel->GetSocketRotation(FName("Projectile"))
		);
}

void ATank::SetBarrelReference(UTankBarrel* barrelToSet) {
	TankAimingComponent->SetBarrelReference(barrelToSet);
	barrel = barrelToSet;
}

void ATank::SetTurretReference(UTankTurret* turretToSet) {
	TankAimingComponent->SetTurretReference(turretToSet);
}
