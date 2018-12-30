// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "SpawnerComponent.h"
#include "Statics.h"
#include "Spawnable.h"

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

TScriptInterface<ISpawnable> USpawnerComponent::Spawn()
{
	const int32 Index = GetSpawnableIndex();
	AActor* SpawnableActor = Cast<AActor>(SpawnableActors[Index].GetDefaultObject());
	ISpawnable* Spawnable = Cast<ISpawnable>(SpawnableActor)->Spawn(CooldownComponent, GetWorld(), GetOwner()->GetTransform());
	SetSpawnTimer();
	return FStatics::CreateScriptInterface<ISpawnable>(Spawnable, SpawnableActor);
}

// Used for cooldown delegate
void USpawnerComponent::CallSpawn()
{
	Spawn();
}

int32 USpawnerComponent::GetSpawnableIndex_Implementation()
{
	return FMath::RandRange(0, SpawnableActors.Num() - 1);
}
