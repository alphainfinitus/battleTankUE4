// Copyright Mridul Kumar

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SprungWheel.generated.h"

//forward declarations
class UPhysicsConstraintComponent;
class USphereComponent;

UCLASS()
class BATTLETANK_API ASprungWheel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASprungWheel();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AddDrivingForce(float forceMagnitude);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

private:

	void SetupConstraint();

	//Components
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* axle = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* wheel = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPhysicsConstraintComponent* axleWheelPhysicsConstraint = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPhysicsConstraintComponent* massWheelPhysicsConstraint = nullptr; //also mass - axle constraint
};
