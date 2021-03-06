// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

//forward declaration
class ASprungWheel;


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = Input)
	void setThrottle(float throttle);

	void DriveTrack(float currentThrottle);

	//max force per track in newton
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float maxDrivingForce = 59900000; // TODO find correct number

private:
	UTankTrack();

	TArray<ASprungWheel*> GetWheels() const;
};
