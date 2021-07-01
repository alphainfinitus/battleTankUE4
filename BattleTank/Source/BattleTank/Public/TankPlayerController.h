// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	ATank* GetControlledTank() const;

	//aim tank barrel at crosshair position
	void AimTowardsCrossHair();

	//return an OUT parameter, true if hits landscape
	bool GetSightRayHitLocation(FVector& HitLocation) const;

	bool GetLookDirection(FVector2D screenLocation, FVector& lookDirection) const;

	bool GetLookDirectionHitLocation(FVector lookDirection, FVector& hitLocation) const;

	UPROPERTY(EditAnywhere)
	float crosshairLocationX = 0.5;

	UPROPERTY(EditAnywhere)
	float crosshairLocationY = 0.33333;

	UPROPERTY(EditAnywhere)
	float lineTraceRange = 1000000;
};
