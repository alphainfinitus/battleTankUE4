// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"

UTankTrack::UTankTrack() {
	PrimaryComponentTick.bCanEverTick = false;
	//set simulation generates hit events  (on blueprint - collision)
	this->SetNotifyRigidBodyCollision(true);
}

void UTankTrack::BeginPlay() {
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::ApplySidewaysForce()
{
	auto rightVector = GetRightVector();

	//Calculate slippage speed (COS of right velocity and forward velocity)
	auto slippageSpeed = FVector::DotProduct(rightVector, GetComponentVelocity());

	//acceleration req. in this frame to correct
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto reqCorrectionAcc = -slippageSpeed / DeltaTime * rightVector;

	//calculate and apply sideways force (F = m x a)
	auto tankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto correctionForce = (tankRoot->GetMass() * reqCorrectionAcc) / 2;

	//apply force 
	tankRoot->AddForce(correctionForce);
}

void UTankTrack::setThrottle(float throttle) {
	currentThrottle = FMath::Clamp<float>(currentThrottle + throttle, -1, 1);
}

void UTankTrack::DriveTrack(){
	auto forceApplied = GetForwardVector() * currentThrottle * maxDrivingForce;

	auto forceLocation = GetComponentLocation();

	auto tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	tankRoot->AddForceAtLocation(forceApplied, forceLocation);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit){
	DriveTrack();
	ApplySidewaysForce();

	//reset throttle
	currentThrottle = 0;
}