// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"


class UTankAimingComponent;
/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:
	void BeginPlay();



private:

	virtual void Tick(float DeltaTime) override;

	void AimTowardsPlayer() const;

	void MoveToPlayer();

	virtual void SetPawn(APawn* InPawn) override;

	UFUNCTION()
	void OnPossessedTankDeath();


protected:
	
	UTankAimingComponent* AimingComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float AcceptanceRadius = 5500; 


};


