// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/TankTrack.h"
#include "Components/PrimitiveComponent.h" 


UTankTrack::UTankTrack() {
	PrimaryComponentTick.bCanEverTick = true;
}


void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2; //Two tracks
	TankRoot->AddForce(CorrectionForce);
}


void UTankTrack::SetThrottle(float Throttle) {
//	UE_LOG(LogTemp, Warning, TEXT("Throttle on track: %f"), Throttle)

	/// TODO: Clamp input value

	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();

	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());	
//	UE_LOG(LogTemp, Warning, TEXT("%s component being moved with %s force: "), *TankRoot->GetName(),*ForceApplied.ToString())
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}
