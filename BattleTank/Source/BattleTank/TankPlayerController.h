// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATank* GetControlledTank() const;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	

private:
	/// Start the tank moving the barrel towards the crosshair, so that shows will hit where crossahirs intersects the world
	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector& Hitlocation);

	bool GetLookVectorHitLocation(FVector& Hitlocation, FVector& LookDirection) const;

	bool GetLookDirection(FVector2D& ScreenLocation, FVector& LookDirection) const;

	UPROPERTY(EditAnywhere)	
	float CrossHairXLocation = 0.5f;
	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = 0.33f;

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000.0f;

	
};


