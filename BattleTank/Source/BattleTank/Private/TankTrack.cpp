// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"
#include "SprungWheel.h"
#include "SpawnPoint.h"

UTankTrack::UTankTrack() {
	PrimaryComponentTick.bCanEverTick = false;
	//set simulation generates hit events  (on blueprint - collision)
	this->SetNotifyRigidBodyCollision(true);
}

void UTankTrack::setThrottle(float throttle) {
	float currentThrottle = FMath::Clamp<float>(throttle, -1, 1);
	DriveTrack(currentThrottle);
}

void UTankTrack::DriveTrack(float currentThrottle){
	auto forceApplied = currentThrottle * maxDrivingForce;
	auto wheels = GetWheels();

	auto forcePerWheel = forceApplied / wheels.Num();

	for (ASprungWheel* wheel : wheels) {
		wheel->AddDrivingForce(forcePerWheel);
	}
}

TArray<ASprungWheel*> UTankTrack::GetWheels() const {
	TArray<ASprungWheel*> wheelsArr;
	TArray<USceneComponent*> children;

	GetChildrenComponents(true, children);

	for (USceneComponent* child : children) {
		auto spawnPointChild = Cast<USpawnPoint>(child);
		if(!spawnPointChild) continue;

		AActor* spawnedChild = spawnPointChild->GetSpawnedActor();
		auto sprungWheel = Cast<ASprungWheel>(spawnedChild);
		if(!sprungWheel) continue;

		wheelsArr.Add(sprungWheel);
	}

	return wheelsArr;
}