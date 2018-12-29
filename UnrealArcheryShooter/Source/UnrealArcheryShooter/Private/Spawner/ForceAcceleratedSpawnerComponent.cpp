// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "ForceAcceleratedSpawnerComponent.h"
#include "DestructibleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "SpawnableActor.h"

UForceAcceleratedSpawnerComponent::UForceAcceleratedSpawnerComponent()
{
	Force = FVector(400, 0, 3000);
}

ASpawnableActor* UForceAcceleratedSpawnerComponent::Spawn_Implementation()
{
	ASpawnableActor* SpawnedActor = Super::Spawn_Implementation();
	if (SpawnedActor)
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
	return SpawnedActor;
}
