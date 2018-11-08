// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "ActorPool.h"

DEFINE_LOG_CATEGORY(LogObjectPool);

APoolableActor* UActorPool::PopActor(FTransform const* Transform, const FActorSpawnParameters& SpawnParameters /*= FActorSpawnParameters()*/)
{
	IPoolableObject* PoolableObject = nullptr;
	if (!Pool.Dequeue(PoolableObject))
	{
		UE_LOG(LogObjectPool, Warning, TEXT("RETURN NEW OBJECT"));
		APoolableActor* PoolableObject = Cast<APoolableActor>(World->SpawnActor(Class, Transform, SpawnParameters));
		PoolableObject->SetSelfPool(this);
		PoolableObject->Enable();
		return PoolableObject;
	}

	APoolableActor* PoolableActor = Cast<APoolableActor>(PoolableObject);

	if (CanEnable(PoolableActor, Transform, SpawnParameters))
	{
		UE_LOG(LogObjectPool, Warning, TEXT("ENABLE CALL"));
		PoolableActor->Enable();
		return PoolableActor;
	}
	else
	{
		UE_LOG(LogObjectPool, Warning, TEXT("ENABLE FAILED !!!"));
		return nullptr;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// -------------------------------- BEGIN (UWorld::SpawnActor part of code by Epic Games) -------------------------------- //

bool UActorPool::CanEnable(APoolableActor* PoolableActor, FTransform const* Transform, const FActorSpawnParameters& SpawnParameters)
{
	if (Transform && Transform->ContainsNaN())
	{
		UE_LOG(LogObjectPool, Warning, TEXT("EnableActor failed because the given transform (%s) is invalid"), *(Transform->ToString()));
		return false;
	}
	FTransform const UserTransform = Transform ? *Transform : FTransform::Identity;

	ESpawnActorCollisionHandlingMethod CollisionHandlingOverride = SpawnParameters.SpawnCollisionHandlingOverride;

	// "no fail" take preedence over collision handling settings that include fails
	if (SpawnParameters.bNoFail)
	{
		HandleNoFailSettings(CollisionHandlingOverride);
	}

	// use override if set, else fall back to actor's preference
	ESpawnActorCollisionHandlingMethod const CollisionHandlingMethod = (CollisionHandlingOverride == ESpawnActorCollisionHandlingMethod::Undefined)
		? PoolableActor->SpawnCollisionHandlingMethod
		: CollisionHandlingOverride;

	// see if we can avoid spawning altogether by checking native components
	// note: we can't handle all cases here, since we don't know the full component hierarchy until after the actor is spawned
	if (CollisionHandlingMethod == ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding)
	{
		if (IsCollidingOnSpawn(PoolableActor, UserTransform))
		{
			UE_LOG(LogObjectPool, Log, TEXT("EnableActor failed because the enabled actor %s is colliding on spawn"), *PoolableActor->GetPathName());
			return false;
		}
	}
	// tell the actor what method to use, in case it was overridden
	PoolableActor->SpawnCollisionHandlingMethod = CollisionHandlingMethod;

	if (PoolableActor->IsPendingKill() && !SpawnParameters.bNoFail)
	{
		UE_LOG(LogObjectPool, Log, TEXT("EnableActor failed because the enabled actor %s IsPendingKill"), *PoolableActor->GetPathName());
		return false;
	}
	PoolableActor->SetActorTransform(UserTransform);
	return true;
}

void UActorPool::HandleNoFailSettings(ESpawnActorCollisionHandlingMethod& CollisionHandlingOverride)
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

bool UActorPool::IsCollidingOnSpawn(APoolableActor* PoolableActor, const FTransform& UserTransform)
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
		UE_LOG(LogObjectPool, Log, TEXT("EnableActor failed because of collision at the spawn location [%s] for [%s]"), *FinalRootLocation.ToString(), *Class->GetName());
		return true;
	}
	return false;
}
// --------------------------------- END (UWorld::SpawnActor part of code by Epic Games) --------------------------------- //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

IPoolableObject* UActorPool::SpawnObject()
{
	IPoolableObject* PoolableObject = Cast<IPoolableObject>(World->SpawnActor(Class));
	PoolableObject->SetSelfPool(this);
	return PoolableObject;
}
