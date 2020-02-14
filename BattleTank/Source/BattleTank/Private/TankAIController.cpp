// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/TankAIController.h"
#include "Public/TankAimingComponent.h"

#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();

	
}

void ATankAIController::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);
	
	AimTowardsPlayer();

	auto ControlledTank = GetPawn();
	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	if (AimingComponent->GetFiringState() == EFiringStatus::Locked) {
		AimingComponent->Fire();
	}
	//TODO: Fix me
	MoveToPlayer();

}

void ATankAIController::AimTowardsPlayer() const {

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();

	if (ensure(PlayerTank && ControlledTank)) {;
		ControlledTank->FindComponentByClass<UTankAimingComponent>()->AimAt(PlayerTank->GetActorLocation());
	}
}

void ATankAIController::MoveToPlayer() {
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (ensure(PlayerTank)) {
		MoveToActor(PlayerTank, AcceptanceRadius);
	}
}
