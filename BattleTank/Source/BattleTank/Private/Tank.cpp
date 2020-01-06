// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "Public/TankAimingComponent.h"
#include "Engine/StaticMeshSocket.h" 
#include "Engine/World.h"
#include "Public/Projectile.h"
#include "Public/TankBarrel.h"
#include "Public/TankMovementComponent.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATank::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("Firing tank"))
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeSeconds;
	if (!Barrel || !isReloaded) { return;  }
	
	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(
		ProjectileBlueprint,
		Barrel->GetSocketLocation(FName("Projectile")),
		Barrel->GetSocketRotation(FName("Projectile"))
	);

	Projectile->Launch(LaunchSpeed);
	LastFireTime = FPlatformTime::Seconds();
}



void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}


void ATank::AimAt(FVector HitLocation) {
//	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

