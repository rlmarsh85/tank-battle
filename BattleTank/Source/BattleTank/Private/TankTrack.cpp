// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/TankTrack.h"
#include "Components/PrimitiveComponent.h" 



void UTankTrack::SetThrottle(float Throttle) {
//	UE_LOG(LogTemp, Warning, TEXT("Throttle on track: %f"), Throttle)

	/// TODO: Clamp input value

	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();

	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());	
//	UE_LOG(LogTemp, Warning, TEXT("%s component being moved with %s force: "), *TankRoot->GetName(),*ForceApplied.ToString())
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}
