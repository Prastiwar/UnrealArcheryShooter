// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "UObject/Object.h"
#include "PoolableActor.h"
#include "ObjectPool.h"
#include "ActorPool.generated.h"

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
	FORCEINLINE APoolableActor* PopActor(FTransform const* Transform, const FActorSpawnParameters& SpawnParameters = FActorSpawnParameters())
	{
		IPoolableObject* PoolableObject = nullptr;
		if (!Pool.Dequeue(PoolableObject))
		{
			UE_LOG(LogTemp, Warning, TEXT("RETURN NEW OBJECT"));
			APoolableActor* PoolableObject = Cast<APoolableActor>(World->SpawnActor(Class, Transform, SpawnParameters));
			PoolableObject->SetSelfPool(this);
			PoolableObject->Enable();
			return PoolableObject;
		}
		APoolableActor* PoolableActor = Cast<APoolableActor>(PoolableObject);

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// -------------------------------- BEGIN (UWorld::SpawnActor part of code by Epic Games) -------------------------------- //

		if (Transform && Transform->ContainsNaN())
		{
			UE_LOG(LogTemp, Warning, TEXT("SpawnActor failed because the given transform (%s) is invalid"), *(Transform->ToString()));
			return nullptr;
		}
		FTransform const UserTransform = Transform ? *Transform : FTransform::Identity;

		ESpawnActorCollisionHandlingMethod CollisionHandlingOverride = SpawnParameters.SpawnCollisionHandlingOverride;
		// "no fail" take preedence over collision handling settings that include fails
		if (SpawnParameters.bNoFail)
		{
			// maybe upgrade to disallow fail
			if (CollisionHandlingOverride == ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding)
			{
				CollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
			}
			else if (CollisionHandlingOverride == ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding)
			{
				CollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			}
		}

		// use override if set, else fall back to actor's preference
		ESpawnActorCollisionHandlingMethod const CollisionHandlingMethod = (CollisionHandlingOverride == ESpawnActorCollisionHandlingMethod::Undefined) 
			? PoolableActor->SpawnCollisionHandlingMethod 
			: CollisionHandlingOverride;

		// see if we can avoid spawning altogether by checking native components
		// note: we can't handle all cases here, since we don't know the full component hierarchy until after the actor is spawned
		if (CollisionHandlingMethod == ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding)
		{
			USceneComponent* const TemplateRootComponent = PoolableActor->GetRootComponent();

			// Note that we respect any initial transformation the root component may have from the CDO, so the final transform
			// might necessarily be exactly the passed-in UserTransform.
			FTransform const FinalRootComponentTransform =
				TemplateRootComponent
				? FTransform(TemplateRootComponent->RelativeRotation, TemplateRootComponent->RelativeLocation, TemplateRootComponent->RelativeScale3D) * UserTransform
				: UserTransform;

			FVector const FinalRootLocation = FinalRootComponentTransform.GetLocation();
			FRotator const FinalRootRotation = FinalRootComponentTransform.Rotator();

			if (World->EncroachingBlockingGeometry(PoolableActor, FinalRootLocation, FinalRootRotation))
			{
				// a native component is colliding, that's enough to reject spawning
				UE_LOG(LogTemp, Log, TEXT("SpawnActor failed because of collision at the spawn location [%s] for [%s]"), *FinalRootLocation.ToString(), *Class->GetName());
				return nullptr;
			}
		}
		// tell the actor what method to use, in case it was overridden
		PoolableActor->SpawnCollisionHandlingMethod = CollisionHandlingMethod;

#if WITH_EDITOR
		PoolableActor->bIsEditorPreviewActor = SpawnParameters.bTemporaryEditorActor;
#endif //WITH_EDITOR
		
		if (PoolableActor->IsPendingKill() && !SpawnParameters.bNoFail)
		{
			UE_LOG(LogTemp, Log, TEXT("SpawnActor failed because the spawned actor %s IsPendingKill"), *PoolableActor->GetPathName());
			return nullptr;
		}

		// --------------------------------- END (UWorld::SpawnActor part of code by Epic Games) --------------------------------- //
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		UE_LOG(LogTemp, Warning, TEXT("ENABLED"));
		PoolableActor->Enable();
		return PoolableActor;
	}

	// Returns new spawned PoolableObject
	FORCEINLINE virtual IPoolableObject* SpawnObject() override
	{
		IPoolableObject* PoolableObject = Cast<IPoolableObject>(World->SpawnActor(Class));
		PoolableObject->SetSelfPool(this);
		return PoolableObject;
	}

};