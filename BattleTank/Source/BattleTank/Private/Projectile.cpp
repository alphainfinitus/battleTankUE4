// Fill out your copyright notice in the Description page of Project Settings.

#include "Particles/ParticleSystemComponent.h"
#include "Projectile.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include "Sound/SoundCue.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	collisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	SetRootComponent(collisionMesh);
	collisionMesh->SetNotifyRigidBodyCollision(true);
	collisionMesh->SetVisibility(false); //TODO Revert to false in production

	launchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
	launchBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	projectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
	projectileMovement->bAutoActivate = false;

	impactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast"));
	impactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	impactBlast->bAutoActivate = false;

	explosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("Explosion Force"));
	explosionForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	//Setup Explosion Sound Cue
	static ConstructorHelpers::FObjectFinder<USoundCue> projectileExplosionSound(TEXT("/Game/Audio/projectile_explosion_short_Cue.projectile_explosion_short_Cue"));
	projectileExplosionSoundCue = projectileExplosionSound.Object;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	collisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

void AProjectile::launchProjectile(float speed){
	projectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * speed);
	projectileMovement->Activate();
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) {
	launchBlast->Deactivate();

	impactBlast->Activate();

	UAudioComponent* AudioComponent = UGameplayStatics::SpawnSoundAtLocation(
		this,
		projectileExplosionSoundCue,
		Hit.Location,
		FRotator::ZeroRotator, 1, 1, 0.0f, nullptr, nullptr, true
	);

	explosionForce->FireImpulse();

	SetRootComponent(impactBlast);
	collisionMesh->DestroyComponent();

	UGameplayStatics::ApplyRadialDamage(
		this,
		projectileDamage,
		GetActorLocation(),
		explosionForce->Radius,
		UDamageType::StaticClass(),
		TArray<AActor*>() //empty array damages all actors

	);

	FTimerHandle timerHandle; //OUT (no-use rn)
	GetWorld()->GetTimerManager().SetTimer(timerHandle, this, &AProjectile::OnTimerExpire, destroyDelay, false);
}

void AProjectile::OnTimerExpire() {
	Destroy();
}