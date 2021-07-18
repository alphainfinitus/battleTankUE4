// Fill out your copyright notice in the Description page of Project Settings.

#include "Particles/ParticleSystemComponent.h"
#include "Projectile.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	collisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	SetRootComponent(collisionMesh);
	collisionMesh->SetNotifyRigidBodyCollision(true);
	collisionMesh->SetVisibility(true); //TODO Revert to false in production

	launchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
	launchBlast->AttachTo(RootComponent);

	projectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
	projectileMovement->bAutoActivate = false;

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::launchProjectile(float speed){
	projectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * speed);
	projectileMovement->Activate();
}

