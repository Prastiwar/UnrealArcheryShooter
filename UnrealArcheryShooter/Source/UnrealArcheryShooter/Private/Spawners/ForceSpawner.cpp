// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "ForceSpawner.h"
#include "DestructibleComponent.h"

AForceSpawner::AForceSpawner()
{
	Force = FVector(400, 0, 3000);
}

void AForceSpawner::SpawnImpl(ASpawnableActor* SpawnedActor)
{
	if (UDestructibleComponent* DM = Cast<UDestructibleComponent>(SpawnedActor->GetRootComponent()))
	{
		DM->SetPhysicsLinearVelocity(Force);
	}
	else if (UStaticMeshComponent* SM = Cast<UStaticMeshComponent>(SpawnedActor->GetRootComponent()))
	{
		SM->SetPhysicsLinearVelocity(Force);
	}
}
