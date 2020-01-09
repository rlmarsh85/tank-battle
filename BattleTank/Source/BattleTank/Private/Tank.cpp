// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "Public/TankAimingComponent.h"
#include "Public/Projectile.h"
#include "Public/TankBarrel.h"

#include "Engine/StaticMeshSocket.h" 
#include "Engine/World.h"


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


	TankAimingComponent = FindComponentByClass<UTankAimingComponent>();
	UE_LOG(LogTemp,Warning, TEXT("TANKBUG: Calling Tank::BeginPlay()"))
	
}

void ATank::Fire()
{
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeSeconds;
	if (!ensure(Barrel) || !isReloaded) { return;  }
	
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
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

