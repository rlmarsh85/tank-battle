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
	PrimaryComponentTick.bCanEverTick = true;



}

void UTankAimingComponent::BeginPlay() {

	//Super::BeginPlay();
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction) {

	//Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (FPlatformTime::Seconds() - LastFireTime < ReloadTimeSeconds){
		UE_LOG(LogTemp,Warning,TEXT("Is Reloading"))
		FiringState = EFiringStatus::Reloading;
	}
	else if (IsBarrelMoving()) {
		UE_LOG(LogTemp, Warning, TEXT("Is Moving"))
		FiringState = EFiringStatus::Ready;
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Is Locked"))
		FiringState = EFiringStatus::Locked;
	}

}

bool UTankAimingComponent::IsBarrelMoving(){
	if (!ensure(Barrel)) {
		return false;
	}
	return (!Barrel->GetForwardVector().Equals(AimDirection, 0.01));

	
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
		
		AimDirection = LaunchVelocity.GetSafeNormal();
		//MoveBarrel(AimDirection);
		//MoveTurret(AimDirection);
		MoveBarrelTowards(AimDirection);
	}

}

void UTankAimingComponent::Initialize(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}




void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!ensure(Barrel) || !ensure(Turret)) { return; }

	// Work-out difference between current barrel roation, and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->ElevateBarrel(DeltaRotator.Pitch);

	if (DeltaRotator.Yaw >= 180) {
		DeltaRotator.Yaw = DeltaRotator.Yaw - 360;
	}
	if (DeltaRotator.Yaw <= -180) {
		DeltaRotator.Yaw = DeltaRotator.Yaw + 360;
	}

	Turret->RotateTurret(DeltaRotator.Yaw);
}

void UTankAimingComponent::Fire()
{


	if (FiringState == EFiringStatus::Reloading) { return; }

	if (!ensure(Barrel)) { return; }
	if (!ensure(ProjectileBlueprint)) { return; }

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

