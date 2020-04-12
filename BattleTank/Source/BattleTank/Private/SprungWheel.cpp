// Copyright Lee Marsh


#include "SprungWheel.h"


#include "Components/PrimitiveComponent.h" 

// Sets default values
ASprungWheel::ASprungWheel()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Constraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("PhysicsConstraint"));
	SetRootComponent(Constraint);

	WheelMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Wheel"));
	WheelMesh->SetNotifyRigidBodyCollision(true);
	WheelMesh->SetVisibility(true);
	WheelMesh->SetupAttachment(Constraint);

}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();

	SetupConstraints();



}

void ASprungWheel::SetupConstraints()
{
	if (GetAttachParentActor()) {
		UE_LOG(LogTemp, Warning, TEXT("parent name: %s"), *GetAttachParentActor()->GetName())
		UPrimitiveComponent* BodyRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
		if (BodyRoot) {
			UE_LOG(LogTemp, Warning, TEXT("Found BodyRoot"), *GetAttachParentActor()->GetName())
			Constraint->SetConstrainedComponents(BodyRoot, NAME_None, WheelMesh, NAME_None);
		}

	}
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



