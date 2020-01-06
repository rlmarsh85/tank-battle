// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/TankMovementComponent.h"
#include "Public/TankTrack.h"




void UTankMovementComponent::IntendMoveForward(float Throw) {

	if (!LeftTrack || !RightTrack) { return; }

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);

}

void UTankMovementComponent::IntendTurnRight(float Throw) {

	if (!LeftTrack || !RightTrack) { return; }

	LeftTrack->SetThrottle(-Throw);
	RightTrack->SetThrottle(Throw);

}


void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet) {

	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();

	IntendMoveForward(FVector::DotProduct(AIForwardIntention, TankForward));
	IntendTurnRight(FVector::CrossProduct(TankForward, AIForwardIntention).Z);
	
	UE_LOG(LogTemp, Warning, TEXT("MoveVelocity : %s Tank Name:%s"), *MoveVelocity.ToString(), *GetOwner()->GetName())
}
