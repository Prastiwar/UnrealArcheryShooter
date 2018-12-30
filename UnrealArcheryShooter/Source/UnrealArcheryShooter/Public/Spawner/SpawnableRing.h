// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "DestructibleComponent.h"
#include "Spawnable.h"
#include "SpawnableRing.generated.h"

UCLASS()
class UNREALARCHERYSHOOTER_API ASpawnableRing : public AActor, public ISpawnable
{
	GENERATED_BODY()

public:
	ASpawnableRing();

	// ISpawnable interface
	virtual bool CanBeSpawned() const override;
	virtual UClass* GetSpawnableClass() const override { return this->GetClass(); }
	/////////////////////////////

	UFUNCTION(BlueprintCallable)
		float GetScore() const;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UDestructibleComponent* DestructibleMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UPointLightComponent* Light;

};
