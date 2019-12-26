// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/TankAIController.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"



ATank* ATankAIController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}


void ATankAIController::BeginPlay() {

	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("AIontroller Begin Play"))

	auto ThisTank = GetControlledTank();
	if (!ThisTank) {
		UE_LOG(LogTemp, Warning, TEXT("Could not find controlled tank in tank AI controller"))
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Found AI controlled tank:%s"), *ThisTank->GetName())
	}

	auto PlayerTank = GetPlayerTank();
	if (!PlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("Could not find player tank in tank AI controller"))
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Found player tank in AI controller"), *PlayerTank->GetName())
	}

}

ATank* ATankAIController::GetPlayerTank() const
{
	ATank* PlayerTank = Cast<ATank>((GetWorld()->GetFirstPlayerController()->GetPawn()));
	
	if (!PlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("Could not find player tank in AI Controller"));
	}

	return PlayerTank;
}

