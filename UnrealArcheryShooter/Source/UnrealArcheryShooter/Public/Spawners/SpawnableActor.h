// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnableActor.generated.h"

UCLASS()
class UNREALARCHERYSHOOTER_API ASpawnableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ASpawnableActor();

	virtual void BeginPlay() override;
	virtual bool CanSpawn() { return true; }

};
