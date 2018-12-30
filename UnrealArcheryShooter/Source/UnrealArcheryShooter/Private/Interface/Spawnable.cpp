// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "Spawnable.h"

bool ISpawnable::CanBeSpawned() const
{
	return true;// CooldownData.bIsCompleted;
}

ISpawnable* ISpawnable::Spawn(UWorld* World, FTransform const& Transform, FActorSpawnParameters SpawnParameters)
{
	return Spawn(nullptr, World, Transform, SpawnParameters);
}

ISpawnable* ISpawnable::Spawn(UCooldownComponent* const CooldownComponent, UWorld* World, FTransform const& Transform, FActorSpawnParameters SpawnParameters)
{
	ISpawnable* Spawnable = nullptr;
	if (CanBeSpawned())
	{
		UE_LOG(LogTemp, Warning, TEXT("SPAWN@"));
		Spawnable = Cast<ISpawnable>(World->SpawnActor<AActor>(GetSpawnableClass(), Transform, SpawnParameters));
		if (CooldownComponent)
		{
			CooldownData = FCooldownData();
			if (UsesCooldownData(CooldownData))
			{
				CooldownComponent->SetCooldown(&CooldownData);
			}
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("CAN NOT SPAWN@"));
	}
	return Spawnable;
}
