// Copyright Lee Marsh


#include "SprungWheel.h"


#include "Components/PrimitiveComponent.h" 

// Sets default values
ASprungWheel::ASprungWheel()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PostPhysics;

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

	WheelMesh->SetNotifyRigidBodyCollision(true);
	WheelMesh->OnComponentHit.AddDynamic(this, &ASprungWheel::OnHit);

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

void ASprungWheel::ApplyForce()
{
	WheelMesh->AddForce(Axle->GetForwardVector() * TotalForceMagnitudeThisFrame);
}

void ASprungWheel::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	ApplyForce();

	
}


void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetWorld()->TickGroup == TG_PostPhysics) {
		TotalForceMagnitudeThisFrame = 0;
	}

}


void ASprungWheel::AddDrivingForce(float ForceMagnitude)
{
//	WheelMesh->AddForce(Axle->GetForwardVector() * ForceMagnitude);
	TotalForceMagnitudeThisFrame += ForceMagnitude	;
}



