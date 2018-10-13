// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "SpawnableBoost.h"

bool ASpawnableBoost::CanBeSpawned() const
{
	ABoost* Boost = nullptr;
	if (BoostToSpawn)
	{
		TArray<FHitResult> HitResults;
		const FVector Location = GetActorLocation();
		const ECollisionChannel ECC = ECollisionChannel::ECC_Visibility;
		FCollisionShape CollisionShape;
		CollisionShape.ShapeType = ECollisionShape::Box;
		CollisionShape.SetBox(GetActorScale() / 2);

		const bool bHitSomething = GetWorld()->SweepMultiByChannel(HitResults, Location, Location, FQuat::FQuat(), ECC, CollisionShape);
		if (!bHitSomething)
		{
			Boost = GetWorld()->SpawnActor<ABoost>(BoostToSpawn, GetTransform());
		}
	}
	return Boost;
}
