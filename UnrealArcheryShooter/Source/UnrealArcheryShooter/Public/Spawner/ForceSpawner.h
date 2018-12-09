// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "OvertimeSpawner.h"
#include "ForceSpawner.generated.h"

UCLASS()
class UNREALARCHERYSHOOTER_API AForceSpawner : public AOvertimeSpawner
{
	GENERATED_BODY()

public:
	AForceSpawner();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector Force;

	virtual void SpawnImpl(class ASpawnableActor* SpawnedActor) override;

};
