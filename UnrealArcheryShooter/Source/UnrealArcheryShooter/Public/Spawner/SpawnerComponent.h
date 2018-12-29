// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "Components/SceneComponent.h"
#include "CooldownData.h"
#include "SpawnerComponent.generated.h"

UCLASS(ClassGroup = (Spawners), meta = (BlueprintSpawnableComponent))
class UNREALARCHERYSHOOTER_API USpawnerComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	USpawnerComponent();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		class ASpawnableActor* Spawn();

protected:
	UPROPERTY(BlueprintReadOnly)
		class UCooldownComponent* CooldownComponent;

	UPROPERTY(EditAnywhere)
		FCooldownData CooldownData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<TSubclassOf<class ASpawnableActor>> SpawnableActors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bSetTimerOnBeginPlay;

	UFUNCTION(BlueprintCallable)
		void SetSpawnTimer();

	// Returns index of Actor to be spawned from SpawnableActors
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		int32 GetSpawnableIndex();

	void CallSpawn();

	virtual int32 GetSpawnableIndex_Implementation();

	virtual class ASpawnableActor* Spawn_Implementation();

	virtual void BeginPlay() override;

};
