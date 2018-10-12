// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "Spawner.h"
#include "CoreMinimal.h"
#include "DestructibleComponent.h"

ASpawner::ASpawner()
{
	PrimaryActorTick.bCanEverTick = false;
	Force = FVector(0, -200, 2000);
	SpawnTimeRange = FVector2D(0.1f, 5.0f);
	TimeToSpawn = 1.0f;
	TimeToDecreaseTime = 30;
}

void ASpawner::BeginPlay()
{
	Super::BeginPlay();
	SetSpawnTimer();
	GetWorld()->GetTimerManager().SetTimer(FrequencyTimerHandle, this, &ASpawner::IncreaseFrequency, ASpawner::TimeToDecreaseTime, true, ASpawner::TimeToDecreaseTime);
}

void ASpawner::IncreaseFrequency()
{
	TimeToSpawn = FMath::Clamp(TimeToSpawn - 0.1f, SpawnTimeRange.X, SpawnTimeRange.Y);
	SetSpawnTimer();
}

void ASpawner::SetSpawnTimer()
{
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &ASpawner::Spawn, ASpawner::TimeToSpawn, true, 0);
}

void ASpawner::Spawn()
{
	int RandIndex = FMath::RandRange(0, SpawnableActors.Num() - 1);
	ASpawnableActor* Spawnable = GetWorld()->SpawnActor<ASpawnableActor>(SpawnableActors[RandIndex], GetTransform());
	if (Spawnable->CanSpawn())
	{
		if (UDestructibleComponent* DM = Cast<UDestructibleComponent>(Spawnable->GetRootComponent()))
		{
			DM->SetPhysicsLinearVelocity(Force);
		}
		else if (UStaticMeshComponent* SM = Cast<UStaticMeshComponent>(Spawnable->GetRootComponent()))
		{
			SM->SetPhysicsLinearVelocity(Force);
		}
	}
	else
	{
		Spawnable->Destroy();
	}
}
