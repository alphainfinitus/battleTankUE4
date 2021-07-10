// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

//Enum for aiming state
UENUM()
enum class EFiringState : uint8 {
	Reloading,
	Aiming,
	Ready
};

//forward declaration
class UTankBarrel;
class UTankTurret;
class AProjectile;

//Holds barrel properties and methods
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	void AimAt(FVector hitLocation);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void Fire();

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel* barrelToSet, UTankTurret* turretToSet);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState firingState = EFiringState::Reloading;

	UPROPERTY(BlueprintReadWrite, Category = "Firing")
	TSubclassOf<AProjectile> projectileBlueprint;

private:
	// Sets default values for this component's properties
	UTankAimingComponent();

	void MoveBarrelTowards(FVector aimDirection);

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float launchSpeed = 500; //TODO: Find sensible default

	UTankBarrel* barrel = nullptr;
	UTankTurret* turret = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float reloadTimeInSeconds = 3;

	double lastFireTime = 0;
	
};