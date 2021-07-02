// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAIController.h"

ATank* ATankAIController::GetAIControlledTank() const {
	return Cast<ATank>(GetPawn());
}

void ATankAIController::BeginPlay() {
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("AI_TankPlayerController BeginPlay called"));

	// log AI controlled tank
	auto AIControlledTank = GetAIControlledTank();

	if (!AIControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("AI_TankPlayerController does not posses a tank"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AI_TankPlayerController posseses: %s"), *(AIControlledTank->GetName()));
	}

	//log player controlled tank

	auto playerTank = GetPlayerTank();

	if (!playerTank) {
		UE_LOG(LogTemp, Warning, TEXT("AI_TankPlayerController could not find player tank"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AI_TankPlayerController found player tank: %s"), *(playerTank->GetName()));
	}
}

ATank* ATankAIController::GetPlayerTank() const {

	auto playerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!playerPawn) {
		return nullptr;
	}

	return Cast<ATank>(playerPawn);
}

//Tick
void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (GetPlayerTank() && GetAIControlledTank()) {
		//MOVE Towards player

		//Aim Towards Player
		AimTowardsPlayerTank();

		//Fire if ready

	}
}

void ATankAIController::AimTowardsPlayerTank() const {
	FVector playerTankLocation =  GetPlayerTank()->GetActorLocation();
	GetAIControlledTank()->AimAt(playerTankLocation);
}