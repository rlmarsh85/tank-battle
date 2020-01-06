// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/TankAIController.h"
#include "Public/Tank.h"

#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);
	
	AimTowardsPlayer();

	ATank* ControlledTank = Cast<ATank>(GetPawn());
	ControlledTank->Fire();
	MoveToPlayer();

}

void ATankAIController::AimTowardsPlayer() const {

	ATank* PlayerTank = Cast<ATank>((GetWorld()->GetFirstPlayerController()->GetPawn()));
	ATank* ControlledTank = Cast<ATank>(GetPawn());

	if (ensure(PlayerTank && ControlledTank)) {
		ControlledTank->AimAt(PlayerTank->GetActorLocation());
	}
}

void ATankAIController::MoveToPlayer() {
	ATank* PlayerTank = Cast<ATank>((GetWorld()->GetFirstPlayerController()->GetPawn()));

	if (ensure(PlayerTank)) {
		MoveToActor(PlayerTank, AcceptanceRadius);
	}
}
