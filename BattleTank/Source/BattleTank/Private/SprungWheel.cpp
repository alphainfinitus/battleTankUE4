// Copyright Mridul Kumar

#include "SprungWheel.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	massWheelPhysicsConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Mass Wheel Physics Constraint"));
	SetRootComponent(massWheelPhysicsConstraint);

	wheel = CreateDefaultSubobject<UStaticMeshComponent>(FName("wheel"));
	wheel->SetupAttachment(massWheelPhysicsConstraint);

}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();

	SetupConstraint();
	
}

void ASprungWheel::SetupConstraint() {
	if (!GetAttachParentActor()) { return; }
	UPrimitiveComponent* bodyRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());

	if (!bodyRoot) { return; }
	massWheelPhysicsConstraint->SetConstrainedComponents(bodyRoot, NAME_None, wheel, NAME_None);
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

