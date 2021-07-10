// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
}

//Tick
void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	auto playerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto aiControlledTank = GetPawn();

	if (!ensure(playerTank && aiControlledTank)) { return; }

	auto aimingComponent = aiControlledTank->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(aimingComponent)) { return; }

	//MOVE Towards player
	MoveToActor(playerTank, acceptanceRadius);

	//Aim Towards Player
	aimingComponent->AimAt(playerTank->GetActorLocation());

	//Fire if ready
	//aimingComponent->Fire();
	
}