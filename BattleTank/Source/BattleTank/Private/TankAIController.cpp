// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
}

//Tick
void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	auto playerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto aiControlledTank = Cast<ATank>(GetPawn());

	if (playerTank) {
		//MOVE Towards player

		//Aim Towards Player
		aiControlledTank->AimAt(playerTank->GetActorLocation());

		//Fire if ready
		aiControlledTank->Fire(); //TODO limit firing rate
	}
}