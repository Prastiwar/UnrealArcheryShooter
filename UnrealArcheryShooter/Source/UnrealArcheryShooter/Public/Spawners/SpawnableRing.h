// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "CoreMinimal.h"
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
	virtual void BeginPlay() override;
	virtual bool CanSpawn() override;

protected:
	UPROPERTY(EditAnywhere, Category = "Spawnable")
		UDestructibleComponent* DestructibleMesh;

	UPROPERTY(EditAnywhere, Category = "Spawnable")
		UPointLightComponent* Light;

public:
	UFUNCTION(BlueprintCallable)
		float GetScore();

};
