// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "SpawnableBoost.h"

ASpawnableBoost::ASpawnableBoost()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ASpawnableBoost::BeginPlay()
{
	Super::BeginPlay();	
}

bool ASpawnableBoost::CanSpawn()
{
	ABoost* Boost = nullptr;
	if (BoostToSpawn)
	{
		TArray<FHitResult> HitResults;
		FVector Location = GetActorLocation();
		ECollisionChannel ECC = ECollisionChannel::ECC_Visibility;
		FCollisionShape CollisionShape;
		CollisionShape.ShapeType = ECollisionShape::Box;
		CollisionShape.SetBox(GetActorScale() / 2);

		bool bHitSomething = GetWorld()->SweepMultiByChannel(HitResults, Location, Location, FQuat::FQuat(), ECC, CollisionShape);
		if (!bHitSomething)
		{
			Boost = GetWorld()->SpawnActor<ABoost>(BoostToSpawn, GetTransform());
		}
	}
	return Boost;
}
