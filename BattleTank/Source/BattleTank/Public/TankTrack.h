// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = Input)
	void setThrottle(float throttle);
	
	//max force per track in newton
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float maxDrivingForce = 400000; // assume tank of mass 40t and 1g acceleration
};
