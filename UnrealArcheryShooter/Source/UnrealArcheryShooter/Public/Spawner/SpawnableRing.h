// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "SpawnableActor.h"
#include "DestructibleComponent.h"
#include "SpawnableRing.generated.h"

UCLASS()
class UNREALARCHERYSHOOTER_API ASpawnableRing : public ASpawnableActor
{
	GENERATED_BODY()

public:
	ASpawnableRing();

	virtual bool CanBeSpawned() const override;

	UFUNCTION(BlueprintCallable)
		float GetScore() const;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UDestructibleComponent* DestructibleMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UPointLightComponent* Light;

};
