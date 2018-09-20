// // Copyright 2018-2019 Tomasz Piowczyk, MIT License

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnData.h"
#include "Components/PointLightComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "SpawnableActor.generated.h"

UCLASS()
class CPPLEARN_API ASpawnableActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASpawnableActor();

protected:
	// Called when the game starts or when spawned
	void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Spawnable")
		UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere, Category = "Spawnable")
		UPointLightComponent* Light;

	UPROPERTY(VisibleAnywhere, Category = "Spawnable")
		FSpawnData SpawnData;

public:
	virtual void Initialize(FSpawnData SpawnData);

	UFUNCTION(BlueprintCallable)
		float GetScore();
};
