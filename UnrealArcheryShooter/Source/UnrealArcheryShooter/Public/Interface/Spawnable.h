// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "UObject/Interface.h"
#include "CooldownData.h"
#include "Spawnable.generated.h"

UINTERFACE(MinimalAPI)
class USpawnable : public UInterface
{
	GENERATED_BODY()
};

class UNREALARCHERYSHOOTER_API ISpawnable
{
	GENERATED_BODY()

public:
	virtual bool CanBeSpawned() const;

	virtual ISpawnable* Spawn(class UCooldownComponent* const CooldownComponent, UWorld* World, FTransform const& Transform, FActorSpawnParameters SpawnParameters = FActorSpawnParameters());

	ISpawnable* Spawn(UWorld* World, FTransform const& Transform, FActorSpawnParameters SpawnParameters = FActorSpawnParameters());

protected:
	virtual UClass* GetSpawnableClass() const { unimplemented(); return nullptr; }

	virtual bool UsesCooldownData(FCooldownData& OutData) const { return false; }

private:
	FCooldownData CooldownData;

};
