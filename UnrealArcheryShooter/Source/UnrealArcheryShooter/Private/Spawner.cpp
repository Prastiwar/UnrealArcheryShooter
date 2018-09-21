// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "Spawner.h"
#include "Engine.h"

ASpawner::ASpawner()
{
	PrimaryActorTick.bCanEverTick = false;
	SpawnDatas = {
		FSpawnData(FLinearColor::Blue, 10),
		FSpawnData(FLinearColor::Red, 20),
		FSpawnData(FLinearColor::Yellow, 40),
		FSpawnData(FLinearColor::Green, 80),
		FSpawnData(FLinearColor::White, 200)
	};
	Force = FVector(0, -200, 2000);
	TimeToIncreaseLevel = 30;
}

void ASpawner::BeginPlay()
{
	Super::BeginPlay();
	SetSpawnTimer();
	GetWorld()->GetTimerManager().SetTimer(LevelTimerHandle, this, &ASpawner::IncreaseLevel, ASpawner::TimeToIncreaseLevel, true, ASpawner::TimeToIncreaseLevel);
}

void ASpawner::IncreaseLevel()
{
	TimeToSpawn = FMath::Clamp(TimeToSpawn - 0.1f, 0.1f, 5.0f);
	SetSpawnTimer();
}

void ASpawner::SetSpawnTimer()
{
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &ASpawner::Spawn, ASpawner::TimeToSpawn, true, 0);
}

void ASpawner::Spawn()
{
	if (ASpawner::SpawnableActor)
	{
		ASpawnableActor* ActorRef = GetWorld()->SpawnActor<ASpawnableActor>(SpawnableActor, GetTransform());
		int RandIndex = FMath::RandRange(0, SpawnDatas.Num() - 1);
		ActorRef->Initialize(SpawnDatas[RandIndex]);

		if (UStaticMeshComponent* SM = Cast<UStaticMeshComponent>(ActorRef->GetRootComponent()))
		{
			SM->SetPhysicsLinearVelocity(Force);
		}
	}
}
