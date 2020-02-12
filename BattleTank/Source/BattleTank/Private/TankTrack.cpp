// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/TankTrack.h"
#include "Components/PrimitiveComponent.h" 


UTankTrack::UTankTrack() {
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay(){
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}




void UTankTrack::ApplySidewaysForce() {
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2; //Two tracks
	TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{	
	DriveTrack();
	ApplySidewaysForce();	
	CurrentThrottle = 0.0f;
}

void UTankTrack::SetThrottle(float Throttle) {
//	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
	CurrentThrottle = CurrentThrottle + Throttle, -1, 1;
}


void UTankTrack::DriveTrack() {

	auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();

	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());	
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}
