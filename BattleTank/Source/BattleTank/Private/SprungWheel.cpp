// Copyright Lee Marsh


#include "SprungWheel.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Constraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("PhysicsConstraint"));
	SetRootComponent(Constraint);

	MassMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mass"));
	MassMesh->SetNotifyRigidBodyCollision(true);
	MassMesh->SetVisibility(true);
	MassMesh->SetupAttachment(Constraint);

	WheelMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Wheel"));
	WheelMesh->SetNotifyRigidBodyCollision(true);
	WheelMesh->SetVisibility(true);
	WheelMesh->SetupAttachment(Constraint);

}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();

	if (GetAttachParentActor()) {
		UE_LOG(LogTemp,Warning, TEXT("parent name: %s"), *GetAttachParentActor()->GetName())
	}

}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

