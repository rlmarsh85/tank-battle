// Fill out your copyright notice in the Description page of Project Settings.



#include "Public/TankPlayerController.h"
#include "Public/TankAimingComponent.h"
#include "Public/Tank.h"

#include "Engine/World.h"



void ATankPlayerController::BeginPlay() {


	Super::BeginPlay();
	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

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


	if (!(ensure(AimingComponent)) ) { return;  }

	if (!GetPawn()) { return;  }

	FVector HitLocation;
	bool bGotHitLocation = GetSightRayHitLocation(HitLocation);
	//if (GetSightRayHitLocation(HitLocation)) {
	if(bGotHitLocation){
		AimingComponent->AimAt(HitLocation);
	}

}

// Get world location through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& Hitlocation) {

	FVector LookDirection;
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
	
	if (GetLookDirection(ScreenLocation,LookDirection)) {
		return GetLookVectorHitLocation(Hitlocation, LookDirection);
	}

	return false;

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

void ATankPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn) {
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossessedTankDeath);
	}
}

void ATankPlayerController::OnPossessedTankDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("Player is dead"))
}
