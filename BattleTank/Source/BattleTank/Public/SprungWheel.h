// Copyright Lee Marsh

#pragma once

#include "Components/SphereComponent.h" 
#include "PhysicsEngine/PhysicsConstraintComponent.h" 
#include "Components/PrimitiveComponent.h" 
#include "Math/Vector.h" 
#include "Engine/EngineTypes.h" 

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SprungWheel.generated.h"

UCLASS()
class BATTLETANK_API ASprungWheel : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASprungWheel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AddDrivingForce(float ForceMagnitude);

private:

	UPROPERTY(VisibleAnywhere, Category = "Setup")
	USphereComponent* WheelMesh = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Setup")
	USphereComponent* Axle = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Setup")
	UPhysicsConstraintComponent* Constraint = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Setup")
	UPhysicsConstraintComponent* AxleWheelConstraint = nullptr;

	void SetupConstraints();

	void ApplyForce();

	float TotalForceMagnitudeThisFrame;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,FVector NormalImpulse, const FHitResult& Hit);

};
