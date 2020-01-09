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

	float AcceptanceRadius = 3000; // TODO assumed in cm


protected:

	UTankAimingComponent* AimingComponent;

};


