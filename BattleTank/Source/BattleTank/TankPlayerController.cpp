// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "Engine/World.h"




ATank* ATankPlayerController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());;
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
		/// UE_LOG(LogTemp, Warning, TEXT("HitLocation:%s"), *HitLocation.ToString())

			/// TODO: Tell controlled tank to aim at this point
	}

}

// Get world location through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& Hitlocation) {

	FVector LookDirection;
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
	/// UE_LOG(LogTemp, Warning, TEXT("ScreenLocation:%s"), *ScreenLocation.ToString())
	if (GetLookDirection(ScreenLocation,LookDirection)) {
		UE_LOG(LogTemp, Warning, TEXT("Look Direction:%s"), *LookDirection.ToString())
	}		
	return true;

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