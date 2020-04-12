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

	Axle = CreateDefaultSubobject<USphereComponent>(FName("Axle"));
	Axle->SetupAttachment(Constraint);

	WheelMesh = CreateDefaultSubobject<USphereComponent>(FName("Wheel"));
	WheelMesh->SetupAttachment(Axle);


	AxleWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("AxleWheelConstraint"));
	AxleWheelConstraint->SetupAttachment(Axle);

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
			Constraint->SetConstrainedComponents(BodyRoot, NAME_None, Axle, NAME_None);
			AxleWheelConstraint->SetConstrainedComponents(Axle, NAME_None, WheelMesh, NAME_None);
		}

	}
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASprungWheel::AddDrivingForce(float ForceMagnitude)
{
	WheelMesh->AddForce(Axle->GetForwardVector() * ForceMagnitude);
}



