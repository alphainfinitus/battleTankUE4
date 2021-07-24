// Fill out your copyright notice in the Description page of Project Settings.

#include <BattleTank/Public/Tank.h>
#include "TankAimingComponent.h"
#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();

	auto aimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(aimingComponent)) {	return;	}

	FoundAimingComponent(aimingComponent);
	
}

//Tick
void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	AimTowardsCrossHair();
}

void ATankPlayerController::SetPawn(APawn* InPawn){
	Super::SetPawn(InPawn);

	if (InPawn) {
		auto possessedTank = Cast<ATank>(InPawn);
		if (!ensure(possessedTank)) { return; }

		//Subscribe local method to tank's death event
		possessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossessedTankDeath);
	}
}

void ATankPlayerController::OnPossessedTankDeath() {
	UE_LOG(LogTemp, Warning, TEXT("Player tank is tank no more"));
	StartSpectatingOnly();
}

void ATankPlayerController::AimTowardsCrossHair() {

	if (!GetPawn()) { return; } //when not possessing ; not using ensure because runtime function

	auto aimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(aimingComponent)) { return; }

	FVector hitLocation; //out parameter

	if (GetSightRayHitLocation(hitLocation)) { //updates hitLocation
		aimingComponent->AimAt(hitLocation);
	}

}

//modifies OUT parameter
//returns true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& hitLocation) const {
	hitLocation = FVector();

	//find the position of the crosshair
	int32 viewportSizeX, viewportSizeY; //OUT parameters
	GetViewportSize(viewportSizeX, viewportSizeY);

	auto screenLocation = FVector2D(viewportSizeX * crosshairLocationX, viewportSizeY * crosshairLocationY);

	FVector lookDirection = FVector();

	//de-project the screen position of the crosshair to world direction
	if (GetLookDirection(screenLocation, lookDirection)) {
		//line trace along the lookDirection and see what we hit on the map (to a max range);
		return GetLookDirectionHitLocation(lookDirection, hitLocation);
	}

	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D screenLocation, FVector& lookDirection) const {
	FVector cameraWorldLocation; //To be discarded (req. for the function out parameter below)
	return DeprojectScreenPositionToWorld(screenLocation.X, screenLocation.Y, cameraWorldLocation, lookDirection);
}

bool ATankPlayerController::GetLookDirectionHitLocation(FVector lookDirection, FVector& hitLocation) const {
	FHitResult hitResult;
	auto startLocation = PlayerCameraManager->GetCameraLocation();
	auto endLocation = startLocation + (lookDirection * lineTraceRange);

	if (GetWorld()->LineTraceSingleByChannel(hitResult, startLocation, endLocation, ECollisionChannel::ECC_Camera)) {
		//line trace succeeds
		//set hit location
		hitLocation = hitResult.Location;
		return true;
	}

	return false; // did not hit anything
};