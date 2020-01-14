// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/TankAimingComponent.h"
#include "Public/TankBarrel.h"
#include "Public/TankTurret.h"
#include "Public/Projectile.h"

#include "Engine/StaticMeshSocket.h" 
#include "Engine/World.h"

#include "Components/ActorComponent.h" 
#include "Containers/Set.h" 
#include "Kismet/GameplayStatics.h" 

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;


	
}

void UTankAimingComponent::AimAt(FVector WorldSpaceAim)
{
	if (!ensure(Barrel && Turret)) { return;  }
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

	if(bHaveAimSolution) {

		auto AimDirection = LaunchVelocity.GetSafeNormal();
		MoveBarrel(AimDirection);
		MoveTurret(AimDirection);
	}

}

void UTankAimingComponent::Initialize(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}


void UTankAimingComponent::MoveBarrel(FVector& AimDirection) {

	if (!ensure(Barrel)) { return; }
	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotation = AimAsRotator - BarrelRotation;

	Barrel->ElevateBarrel(DeltaRotation.Pitch);
}

void UTankAimingComponent::MoveTurret(FVector & AimDirection)
{

	if (!ensure(Turret)) { return;  }
	auto TurretRotation = Turret->GetRelativeRotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotation = AimAsRotator - TurretRotation;
	
	if (DeltaRotation.Yaw >= 180) {
		DeltaRotation.Yaw = DeltaRotation.Yaw - 360;
	}
	if (DeltaRotation.Yaw <= -180) {
		DeltaRotation.Yaw = DeltaRotation.Yaw + 360;
	}

	Turret->RotateTurret(DeltaRotation.Yaw);
}

void UTankAimingComponent::Fire()
{
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeSeconds;
	if (!ensure(Barrel && ProjectileBlueprint)  || !isReloaded) { return; }

	auto Projectile = GetWorld()->SpawnActor<AProjectile>(
		ProjectileBlueprint,
		Barrel->GetSocketLocation(FName("Projectile")),
		Barrel->GetSocketRotation(FName("Projectile"))
		);

	Projectile->Launch(LaunchSpeed);
	LastFireTime = FPlatformTime::Seconds();
}


void UTankAimingComponent::SetProjectileBPClass(TSubclassOf <class AProjectile> ClassIn) {
	ProjectileBlueprint = ClassIn;
}

