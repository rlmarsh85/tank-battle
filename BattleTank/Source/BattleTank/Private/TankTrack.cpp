// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/TankTrack.h"
#include "Components/PrimitiveComponent.h" 


UTankTrack::UTankTrack() {
	PrimaryComponentTick.bCanEverTick = false;
}


void UTankTrack::SetThrottle(float Throttle) {
	float CurrentThrottle = FMath::Clamp<float>(Throttle, -1, 1);
	DriveTrack(CurrentThrottle);
}


void UTankTrack::DriveTrack(float CurrentThrottle) {

	auto ForceApplied = CurrentThrottle * TrackMaxDrivingForce;
	auto Wheels = GetWheels();

	auto ForcePerWheel = ForceApplied / Wheels.Num();

	for (ASprungWheel* Wheel : Wheels) {
		Wheel->AddDrivingForce(ForcePerWheel);
	}

}

TArray<ASprungWheel*> UTankTrack::GetWheels() const
{
	TArray<ASprungWheel*> Wheels = TArray<ASprungWheel*>();
	
	TArray<USceneComponent*>Children;
	GetChildrenComponents(true, Children);

	for (USceneComponent* Child : Children) {

		auto SpawnPointChild = Cast<USpawnPoint>(Child);
		if (!SpawnPointChild) { continue;  }

		AActor* SpawnedChild = SpawnPointChild->GetSpawnedActor();
		auto SprungWheel = Cast<ASprungWheel>(SpawnedChild);

		if (!SprungWheel) { continue;  }

		Wheels.Add(SprungWheel);
	}

	return Wheels;
}
