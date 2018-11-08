// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "UObject/Object.h"
#include "PoolableActor.h"
#include "ObjectPool.h"
#include "ActorPool.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogObjectPool, Log, All)

UCLASS()
class UActorPool : public UObject, public IObjectPool
{
	GENERATED_BODY()

public:
	// Returns casted PoolableObject from pool or returns new spawned object with proper parameters
	template<class T>
	FORCEINLINE T* PopActor(const FActorSpawnParameters& SpawnNewParams)
	{
		return Cast<T>(PopActor(SpawnNewParams));
	}

	// Returns casted PoolableObject from pool or returns new spawned object with proper parameters
	template<class T>
	FORCEINLINE T* PopActor(FVector const* Location, FRotator const* Rotation = NULL, const FActorSpawnParameters& SpawnParameters = FActorSpawnParameters())
	{
		return Cast<T>(PopActor(Location, Rotation, SpawnParameters));
	}

	// Returns casted PoolableObject from pool or returns new spawned object with proper parameters
	template<class T>
	FORCEINLINE T* PopActor(FVector const& Location, FRotator const& Rotation, const FActorSpawnParameters& SpawnParameters = FActorSpawnParameters())
	{
		return Cast<T>(PopActor(Location, Rotation, SpawnParameters));
	}

	// Returns casted PoolableObject from pool or returns new spawned object with proper parameters
	template<class T>
	FORCEINLINE T* PopActor(FTransform const* Transform, const FActorSpawnParameters& SpawnParameters = FActorSpawnParameters())
	{
		return Cast<T>(PopActor(Transform, SpawnParameters));
	}

	// Returns casted PoolableObject from pool or returns new spawned object with proper parameters
	template<class T>
	FORCEINLINE T* PopActor(FTransform const& Transform, const FActorSpawnParameters& SpawnParameters = FActorSpawnParameters())
	{
		return Cast<T>(PopActor(Transform, SpawnParameters));
	}

	// Returns PoolableObject from pool or returns new spawned object with proper parameters
	FORCEINLINE APoolableActor* PopActor(const FActorSpawnParameters& SpawnParameters)
	{
		return PopActor(NULL, NULL, SpawnParameters);
	}

	// Returns PoolableObject from pool or returns new spawned object with proper parameters
	FORCEINLINE APoolableActor* PopActor(FVector const* Location, FRotator const* Rotation = NULL, const FActorSpawnParameters& SpawnParameters = FActorSpawnParameters())
	{
		FTransform Transform;
		if (Location)
		{
			Transform.SetLocation(*Location);
		}
		if (Rotation)
		{
			Transform.SetRotation(FQuat(*Rotation));
		}
		return PopActor(&Transform, SpawnParameters);
	}

	// Returns PoolableObject from pool or returns new spawned object with proper parameters
	FORCEINLINE APoolableActor* PopActor(FVector const& Location, FRotator const& Rotation, const FActorSpawnParameters& SpawnParameters = FActorSpawnParameters())
	{
		return PopActor(&Location, &Rotation, SpawnParameters);
	}

	// Returns PoolableObject from pool or returns new spawned object with proper parameters
	FORCEINLINE APoolableActor* PopActor(FTransform const& Transform, const FActorSpawnParameters& SpawnParameters = FActorSpawnParameters())
	{
		return PopActor(&Transform, SpawnParameters);
	}

	// Returns PoolableObject from pool or returns new spawned object with proper parameters
	APoolableActor* PopActor(FTransform const* Transform, const FActorSpawnParameters& SpawnParameters = FActorSpawnParameters());

	// -------------------------------- BEGIN (UWorld::SpawnActor part of code by Epic Games) -------------------------------- //
	bool CanEnable(APoolableActor* PoolableActor, FTransform const* Transform, const FActorSpawnParameters& SpawnParameters);

	void HandleNoFailSettings(ESpawnActorCollisionHandlingMethod& CollisionHandlingOverride);

	bool IsCollidingOnSpawn(APoolableActor* PoolableActor, const FTransform& UserTransform);
	// --------------------------------- END (UWorld::SpawnActor part of code by Epic Games) --------------------------------- //

	// --------------- BEGIN IObjectPool Interface --------------- //
	// Returns new spawned PoolableObject
	virtual IPoolableObject* SpawnObject() override;
	// ---------------- END IObjectPool Interface ---------------- //
};