// Fill out your copyright notice in the Description page of Project Settings.

#include <BattleTank/Public/Tank.h>
#include "TankAimingComponent.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn) {
		auto possessedTank = Cast<ATank>(InPawn);
		if (!ensure(possessedTank)) { return; }

		//Subscribe local method to tank's death event
		possessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
	}

}

void ATankAIController::OnPossessedTankDeath(){
	UE_LOG(LogTemp, Warning, TEXT("Possessed tank is tank no more"));
	if (!GetPawn()) { return; }
	GetPawn()->DetachFromControllerPendingDestroy();
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

	if (aimingComponent->GetFiringState() == EFiringState::Ready) {
		aimingComponent->Fire();
	}
	
}
