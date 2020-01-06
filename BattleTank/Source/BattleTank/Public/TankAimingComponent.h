// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


/// Enum for aiming state
UENUM()
enum class EFiringStatus : uint8 {
	Reloading,
	Locked,
	Ready
};

//Forward declaration
class UTankBarrel; 
class UTankTurret;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void AimAt(FVector WorldSpaceAim, float LaunchSpeed);

	UFUNCTION(BlueprintCallable, category = Setup)
	void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);


private:

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	void MoveBarrel(FVector& AimDirection);
	void MoveTurret(FVector& AimDirection);

protected:
	UPROPERTY(BlueprintReadOnly, category=State)
	EFiringStatus AimingStatus = EFiringStatus::Reloading;

		
};
