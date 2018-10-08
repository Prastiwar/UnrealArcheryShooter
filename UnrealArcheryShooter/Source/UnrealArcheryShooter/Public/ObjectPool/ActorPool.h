// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "ObjectPool.h"
#include "Queue.h"

template<typename ObjectType>
class UNREALARCHERYSHOOTER_API TActorPool : TObjectPool<ObjectType>
{
public:
	TActorPool(const UWorld* World, const ObjectType* Ptr, const int32 Count) : TObjectPool(World, Ptr, Count) {	}

	virtual ~TActorPool() override
	{
		Pool->~TQueue();
	}

protected:
	virtual void OnPush(ObjectType* Obj) override {	}

	virtual ObjectType* CreateNewObject() override
	{
		return World->SpawnActor(Ptr);
	}
};