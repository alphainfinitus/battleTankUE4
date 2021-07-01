// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"

ATank* ATankPlayerController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();

	auto controlledTank = GetControlledTank();

	if (!controlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("TankPlayerController does not posses a tank"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("TankPlayerController posseses: %s"), *(controlledTank->GetName()));
	}

	UE_LOG(LogTemp, Warning, TEXT("TankPlayerController BeginPlay called"));
}

//Tick
void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	AimTowardsCrossHair();
}

void ATankPlayerController::AimTowardsCrossHair() {
	if (!GetControlledTank()) { return; }

	FVector hitLocation; //out parameter

	if (GetSightRayHitLocation(hitLocation)) { //updates hitLocation
		GetControlledTank()->AimAt(hitLocation);
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
		GetLookDirectionHitLocation(lookDirection, hitLocation);
	}

	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D screenLocation, FVector& lookDirection) const {
	FVector cameraWorldLocation; //To be discarded (req. for the function out parameter below)
	return DeprojectScreenPositionToWorld(screenLocation.X, screenLocation.Y, cameraWorldLocation, lookDirection);
}

bool ATankPlayerController::GetLookDirectionHitLocation(FVector lookDirection, FVector& hitLocation) const {
	FHitResult hitResult;
	auto startLocation = PlayerCameraManager->GetCameraLocation();
	auto endLocation = startLocation + (lookDirection * lineTraceRange);

	if (GetWorld()->LineTraceSingleByChannel(hitResult, startLocation, endLocation, ECollisionChannel::ECC_Visibility)) {
		//line trace succeeds
		//set hit location
		hitLocation = hitResult.Location;
		return true;
	}

	return false; // did not hit anything
};