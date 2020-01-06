// Fill out your copyright notice in the Description page of Project Settings.



#include "Public/TankPlayerController.h"
#include "Public/TankAimingComponent.h"
#include "Engine/World.h"
#include "Public/Tank.h"


ATank* ATankPlayerController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}


void ATankPlayerController::BeginPlay() {


	Super::BeginPlay();
	auto AimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();

	if (ensure(AimingComponent)) {
		FoundAimingComponent(AimingComponent);

	}else {
		UE_LOG(LogTemp, Warning, TEXT("No aiming component found on tank during BeginPlay()"))
	}

}


// Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();

}


void ATankPlayerController::AimTowardsCrosshair() {

	if (!ensure(GetControlledTank())) { return;  }

	FVector HitLocation;

	if (GetSightRayHitLocation(HitLocation)) {
		GetControlledTank()->AimAt(HitLocation);
	}

}

// Get world location through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& Hitlocation) {

	FVector LookDirection;
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
	
	if (GetLookDirection(ScreenLocation,LookDirection)) {
		GetLookVectorHitLocation(Hitlocation, LookDirection);
	}

	return true;

}

bool ATankPlayerController::GetLookVectorHitLocation(FVector& Hitlocation, FVector& LookDirection) const {

	FHitResult LineTraceResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

	if (GetWorld()->LineTraceSingleByChannel(
		LineTraceResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility)
	) {
		Hitlocation = LineTraceResult.Location;
		return true;
	}
	else {
		Hitlocation = FVector(0);
		return false;
	}


}

bool ATankPlayerController::GetLookDirection(FVector2D& ScreenLocation, FVector& LookDirection) const {
	FVector WorldLocation;
	
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		WorldLocation,
		LookDirection
	);		
}