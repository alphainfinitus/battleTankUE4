// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;
class USoundCue;

// For driving the tank tracks
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendMoveForward(float throwValue);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendTurnRight(float throwValue);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankTrack* leftTrackToSet, UTankTrack* rightTrackToSet);

	// Sets default values for playing sound
	UTankMovementComponent();

protected:
	UPROPERTY()
	USoundCue* tankMovingSoundCue;

private:
	//call from path-finding logic by the ai controller
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

	UTankTrack* leftTrack = nullptr;
	UTankTrack* rightTrack = nullptr;
};
