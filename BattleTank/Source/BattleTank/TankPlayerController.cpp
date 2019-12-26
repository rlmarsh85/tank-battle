// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"




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