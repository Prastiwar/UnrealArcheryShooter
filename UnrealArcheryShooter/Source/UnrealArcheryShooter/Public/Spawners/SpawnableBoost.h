// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spawners/SpawnableActor.h"
#include "Boosts/Boost.h"
#include "SpawnableBoost.generated.h"

UCLASS()
class UNREALARCHERYSHOOTER_API ASpawnableBoost : public ASpawnableActor
{
	GENERATED_BODY()

public:
	ASpawnableBoost();

protected:
	virtual void BeginPlay() override;
	virtual bool CanSpawn() override;

	UPROPERTY(EditAnywhere)
		TSubclassOf<ABoost> BoostToSpawn;

};
