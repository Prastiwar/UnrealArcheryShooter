// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

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
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TSubclassOf<ABoost> BoostToSpawn;

	virtual bool CanSpawn() override;

};
