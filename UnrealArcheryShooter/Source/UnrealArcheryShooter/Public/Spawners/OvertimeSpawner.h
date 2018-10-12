// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spawners/SpawnableActor.h"
#include "OvertimeSpawner.generated.h"

UCLASS()
class UNREALARCHERYSHOOTER_API AOvertimeSpawner : public AActor
{
	GENERATED_BODY()

public:
	AOvertimeSpawner();

	UFUNCTION(BlueprintCallable)
		void Spawn();

	UFUNCTION(BlueprintCallable)
		void ChangeFrequency();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<TSubclassOf<class ASpawnableActor>> SpawnableActors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector2D SpawnTimeLimitRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float TimeToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float TimeToChangeFrequency;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ChangeFrequencyAmount;

	FTimerHandle SpawnTimerHandle;
	FTimerHandle FrequencyTimerHandle;

	UFUNCTION(BlueprintCallable)
		void SetSpawnTimer();

	// Returns index of Actor to be spawned from SpawnableActors
	virtual int GetSpawnableIndex();
	virtual void SpawnImpl(ASpawnableActor* SpawnedActor) {}
	virtual void BeginPlay() override;
	
};
