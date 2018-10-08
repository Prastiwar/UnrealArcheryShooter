// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "GameFramework/Actor.h"
#include "SpawnableActor.h"
#include "Spawner.generated.h"

UCLASS()
class UNREALARCHERYSHOOTER_API ASpawner : public AActor
{
	GENERATED_BODY()

public:
	ASpawner();

	UFUNCTION(BlueprintCallable)
		void Spawn();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<TSubclassOf<class ASpawnableActor>> SpawnableActors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector2D SpawnTimeRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float TimeToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float TimeToDecreaseTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector Force;

	FTimerHandle SpawnTimerHandle;
	FTimerHandle FrequencyTimerHandle;

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
		void IncreaseFrequency();

	UFUNCTION(BlueprintCallable)
		void SetSpawnTimer();
};
