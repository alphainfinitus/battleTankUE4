// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

//Forward declarations
class UTankAimingComponent;

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* aimingComponentRef);

private:
	virtual void SetPawn(APawn* InPawn) override;

	UFUNCTION()
	void OnPossessedTankDeath();

	//aim tank barrel at crosshair position
	void AimTowardsCrossHair();

	//return an OUT parameter, true if hits landscape
	bool GetSightRayHitLocation(FVector& HitLocation) const;

	bool GetLookDirection(FVector2D screenLocation, FVector& lookDirection) const;

	bool GetLookDirectionHitLocation(FVector lookDirection, FVector& hitLocation) const;

	UPROPERTY(EditDefaultsOnly)
	float crosshairLocationX = 0.5;

	UPROPERTY(EditDefaultsOnly)
	float crosshairLocationY = 0.33333;

	UPROPERTY(EditDefaultsOnly)
	float lineTraceRange = 1000000;
};
