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
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
		void IncreaseFrequency();

	UFUNCTION(BlueprintCallable)
		void SetSpawnTimer();

	FTimerHandle SpawnTimerHandle;
	FTimerHandle FrequencyTimerHandle;
	
	UPROPERTY(EditAnywhere, Category = "Spawner")
		FVector2D SpawnTimeRange;

	UPROPERTY(EditAnywhere, Category = "Spawner")
		float TimeToSpawn;

	UPROPERTY(EditAnywhere, Category = "Spawner")
		float TimeToDecreaseTime;

	UPROPERTY(EditAnywhere, Category = "Spawner")
		TArray<TSubclassOf<class ASpawnableActor>> SpawnableActors;

	UPROPERTY(EditAnywhere, Category = "Spawner")
		FVector Force;

};
