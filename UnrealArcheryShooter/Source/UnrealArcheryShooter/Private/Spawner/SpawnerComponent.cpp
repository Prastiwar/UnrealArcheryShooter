// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "SpawnerComponent.h"
#include "Statics.h"
#include "SpawnableActor.h"

USpawnerComponent::USpawnerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bSetTimerOnBeginPlay = true;
}

void USpawnerComponent::BeginPlay()
{
	Super::BeginPlay();
	CooldownComponent = FStatics::GetComponentByClass<UCooldownComponent>(GetOwner());
	if (CooldownComponent)
	{
		CooldownData.OnCompleted.AddUObject(this, &USpawnerComponent::CallSpawn);
		if (bSetTimerOnBeginPlay)
		{
			SetSpawnTimer();
		}
	}
}

void USpawnerComponent::SetSpawnTimer()
{
	CooldownComponent->SetCooldown(&CooldownData);
}

ASpawnableActor* USpawnerComponent::Spawn_Implementation()
{
	const int32 Index = GetSpawnableIndex();
	ASpawnableActor* Spawnable = GetWorld()->SpawnActor<ASpawnableActor>(SpawnableActors[Index], GetOwner()->GetTransform());
	if (Spawnable->CanBeSpawned())
	{
		return Spawnable;
	}
	else
	{
		Spawnable->Destroy();
		return nullptr;
	}
}

void USpawnerComponent::CallSpawn()
{
	Spawn();
	SetSpawnTimer();
}

int32 USpawnerComponent::GetSpawnableIndex_Implementation()
{
	return FMath::RandRange(0, SpawnableActors.Num() - 1);
}
