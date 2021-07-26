// Copyright Mridul Kumar

#include "SprungWheel.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//actually mass axle physics constraint
	massWheelPhysicsConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Mass Wheel Physics Constraint"));
	SetRootComponent(massWheelPhysicsConstraint);

	axle = CreateDefaultSubobject<USphereComponent>(FName("axle"));
	axle->SetupAttachment(massWheelPhysicsConstraint);

	wheel = CreateDefaultSubobject<USphereComponent>(FName("wheel"));
	wheel->SetupAttachment(axle);

	axleWheelPhysicsConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Axle Wheel Physics Constraint"));
	axleWheelPhysicsConstraint->SetupAttachment(axle);
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
	massWheelPhysicsConstraint->SetConstrainedComponents(bodyRoot, NAME_None, axle, NAME_None);
	axleWheelPhysicsConstraint->SetConstrainedComponents(axle, NAME_None, wheel, NAME_None);
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

