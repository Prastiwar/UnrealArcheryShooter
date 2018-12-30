// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "ForceAcceleratedSpawnerComponent.h"
#include "DestructibleComponent.h"
#include "Components/StaticMeshComponent.h"

UForceAcceleratedSpawnerComponent::UForceAcceleratedSpawnerComponent()
{
	Force = FVector(400, 0, 3000);
}

TScriptInterface<ISpawnable> UForceAcceleratedSpawnerComponent::Spawn()
{
	TScriptInterface<ISpawnable> Spawnable = Super::Spawn();
	if (Spawnable)
	{
		AActor* SpawnedActor = Cast<AActor>(Spawnable->_getUObject());
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
	}
	return Spawnable;
}
