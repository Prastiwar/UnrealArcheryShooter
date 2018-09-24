// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/PointLightComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Data/SpawnData.h"
#include "DestructibleComponent.h"
#include "SpawnableActor.generated.h"

UCLASS()
class UNREALARCHERYSHOOTER_API ASpawnableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ASpawnableActor();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, Category = "Spawnable")
		UDestructibleComponent* DestructibleMesh;

	UPROPERTY(EditAnywhere, Category = "Spawnable")
		UPointLightComponent* Light;

	UPROPERTY(VisibleAnywhere, Category = "Spawnable")
		FSpawnData SpawnData;

public:
	virtual void Initialize(FSpawnData SpawnData);

	UFUNCTION(BlueprintCallable)
		float GetScore();
};
