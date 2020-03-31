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
	Ready,
	OutOfAmmo
};

//Forward declaration
class UTankBarrel; 
class UTankTurret;
class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void AimAt(FVector WorldSpaceAim);

	EFiringStatus GetFiringState() const;

	UFUNCTION(BlueprintCallable, category = "Setup")
	void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	UFUNCTION(BlueprintCallable, category = "Firing")
	int getRoundsLeft() const;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 4000.0f;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Fire();

	UFUNCTION(BlueprintCallable, category = "Setup")
	void SetProjectileBPClass(TSubclassOf <class AProjectile> ClassIn);

	


private:

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	void MoveBarrelTowards(FVector AimDirection);

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float ReloadTimeSeconds = 3.0f;

	double LastFireTime = 0;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction) override;

	virtual void BeginPlay() override;

	virtual bool IsBarrelMoving();

	int roundsLeft = 3;





protected:

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf < class AProjectile > ProjectileBlueprint = nullptr;

	FVector AimDirection;

	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringStatus FiringState = EFiringStatus::Reloading;
		
};
