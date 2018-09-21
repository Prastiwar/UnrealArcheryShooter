// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnableActor.h"
#include "Data/SpawnData.h"
#include "Spawner.generated.h"

UCLASS()
class UNREALARCHERYSHOOTER_API ASpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	ASpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
		void IncreaseLevel();

	UFUNCTION(BlueprintCallable)
		void SetSpawnTimer();

private:
	FTimerHandle SpawnTimerHandle;
	FTimerHandle LevelTimerHandle;
	float ActualTimeToSpawn;

	UPROPERTY(EditAnywhere, Category = "Spawner")
		float TimeToSpawn;

	UPROPERTY(EditAnywhere, Category = "Spawner")
		float TimeToIncreaseLevel;

	UPROPERTY(EditAnywhere, Category = "Spawner")
		TSubclassOf<class ASpawnableActor> SpawnableActor;

	UPROPERTY(EditAnywhere, Category = "Spawner")
		FVector Force;

	UPROPERTY(EditAnywhere, Category = "Spawner")
		TArray<FSpawnData> SpawnDatas;

	UFUNCTION(BlueprintCallable)
		void Spawn();

};
