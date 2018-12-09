// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "OvertimeSpawner.h"
#include "SpawnableActor.h"

AOvertimeSpawner::AOvertimeSpawner()
{
	PrimaryActorTick.bCanEverTick = false;
	SpawnTimeLimitRange = FVector2D(0.1f, 5.0f);
	TimeToSpawn = 1.0f;
	TimeToChangeFrequency = 30;
	ChangeFrequencyAmount = 0.1f;
}

void AOvertimeSpawner::BeginPlay()
{
	Super::BeginPlay();

	SetSpawnTimer();
	GetWorld()->GetTimerManager().SetTimer(
		FrequencyTimerHandle, this, &AOvertimeSpawner::ChangeFrequency, AOvertimeSpawner::TimeToChangeFrequency, true, AOvertimeSpawner::TimeToChangeFrequency);
}

void AOvertimeSpawner::ChangeFrequency()
{
	TimeToSpawn = FMath::Clamp(TimeToSpawn - ChangeFrequencyAmount, SpawnTimeLimitRange.X, SpawnTimeLimitRange.Y);
	if (TimeToSpawn <= SpawnTimeLimitRange.X || TimeToSpawn >= SpawnTimeLimitRange.Y)
	{
		GetWorld()->GetTimerManager().ClearTimer(FrequencyTimerHandle);
	}
	SetSpawnTimer();
}

void AOvertimeSpawner::SetSpawnTimer()
{
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &AOvertimeSpawner::Spawn, AOvertimeSpawner::TimeToSpawn, true, 0);
}

void AOvertimeSpawner::Spawn()
{
	const int32 Index = GetSpawnableIndex();
	ASpawnableActor* Spawnable = GetWorld()->SpawnActor<ASpawnableActor>(SpawnableActors[Index], GetTransform());
	if (Spawnable->CanBeSpawned())
	{
		SpawnImpl(Spawnable);
	}
	else
	{
		Spawnable->Destroy();
	}
}

int32 AOvertimeSpawner::GetSpawnableIndex()
{
	return FMath::RandRange(0, SpawnableActors.Num() - 1);
}
