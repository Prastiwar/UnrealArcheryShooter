// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "Spawner/AcceleratedSpawnerComponent.h"
#include "ForceAcceleratedSpawnerComponent.generated.h"

UCLASS(ClassGroup = (Spawners), meta = (BlueprintSpawnableComponent))
class UNREALARCHERYSHOOTER_API UForceAcceleratedSpawnerComponent : public UAcceleratedSpawnerComponent
{
	GENERATED_BODY()

public:
	UForceAcceleratedSpawnerComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector Force;

protected:
	virtual class ASpawnableActor* Spawn_Implementation() override;

};
