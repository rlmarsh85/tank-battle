// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/TankAimingComponent.h"
#include "Components/ActorComponent.h" 
#include "Containers/Set.h" 
#include "Kismet/GameplayStatics.h" 
#include "Public/TankBarrel.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
}


void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::AimAt(FVector WorldSpaceAim, float LaunchSpeed)
{
	if (!Barrel) { return;  }
	auto ComponentOwner = GetOwner();

	auto BarrelLocation = Barrel->GetComponentLocation();
	FVector LaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	bool bHaveAimSolution =
		UGameplayStatics::SuggestProjectileVelocity(
			this,
			LaunchVelocity,
			StartLocation,
			WorldSpaceAim,
			LaunchSpeed,
			false,
			0.0f,
			0.0f,
			ESuggestProjVelocityTraceOption::DoNotTrace
		);
	auto Time = GetWorld()->GetTimeSeconds();
	if(bHaveAimSolution) {

		auto AimDirection = LaunchVelocity.GetSafeNormal();
		MoveBarrel(AimDirection);
		UE_LOG(LogTemp, Warning, TEXT("%f: Aim solution found at %s"), Time, *AimDirection.ToString());
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("%f: No aim solution"), Time);
	}
}


void UTankAimingComponent::MoveBarrel(FVector& AimDirection) {

	//Get the barrel
	auto BarrelRoation = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotation = AimAsRotator - BarrelRoation;

	Barrel->ElevateBarrel(DeltaRotation.Pitch);
	UE_LOG(LogTemp, Warning, TEXT("Aim Rotation: %s"), *AimAsRotator.ToString());

}
