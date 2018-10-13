// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "Spawners/SpawnableActor.h"
#include "DestructibleComponent.h"
#include "Components/PointLightComponent.h"
#include "SpawnableRing.generated.h"

UCLASS()
class UNREALARCHERYSHOOTER_API ASpawnableRing : public ASpawnableActor
{
	GENERATED_BODY()

public:
	ASpawnableRing();

	virtual bool CanBeSpawned() const override;

	UFUNCTION(BlueprintCallable)
		float GetScore();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UDestructibleComponent* DestructibleMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UPointLightComponent* Light;

};
