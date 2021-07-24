// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

//Enum for aiming state
UENUM()
enum class EFiringState : uint8 {
	OutOfAmmo,
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
	virtual void BeginPlay() override;

	void AimAt(FVector hitLocation);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void Fire();

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel* barrelToSet, UTankTurret* turretToSet);

	EFiringState GetFiringState() const;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	int32 GetAmmoCount() const;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Firing")
	EFiringState firingState = EFiringState::Reloading;

	UPROPERTY(BlueprintReadWrite, Category = "Firing")
	TSubclassOf<AProjectile> projectileBlueprint;

private:
	// Sets default values for this component's properties
	UTankAimingComponent();

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void MoveBarrelTowardsAimDirection();

	UTankBarrel* barrel = nullptr;
	UTankTurret* turret = nullptr;

	bool IsBarrelMoving();

	FVector aimDirection;

	double lastFireTime = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float reloadTimeInSeconds = 3;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float launchSpeed = 8000; //TODO: Find sensible default

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	int32 ammoCount = 20;
};