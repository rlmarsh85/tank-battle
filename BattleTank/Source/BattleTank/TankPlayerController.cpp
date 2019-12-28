// Fill out your copyright notice in the Description page of Project Settings.



#include "TankPlayerController.h"
#include "Engine/World.h"
#include "Tank.h"


ATank* ATankPlayerController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}


void ATankPlayerController::BeginPlay() {


	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play"))

	auto thisTank = GetControlledTank();
	if (!thisTank) {
		UE_LOG(LogTemp, Warning, TEXT("Could not find controlled tank in tank player controller"))
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Found player controlled tank:%s"), *thisTank->GetName())
	}

}


// Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();

}


void ATankPlayerController::AimTowardsCrosshair() {

	if (!GetControlledTank()) { return;  }

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