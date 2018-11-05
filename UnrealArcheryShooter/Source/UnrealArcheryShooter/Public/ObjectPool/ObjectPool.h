 // Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "UObject/Interface.h"
#include "Queue.h"
#include "ObjectPool/PoolableObject.h"
#include "ObjectPool.generated.h"

UINTERFACE(Blueprintable)
class UObjectPool : public UInterface
{
	GENERATED_BODY()
};

class IObjectPool
{
	GENERATED_BODY()
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnPush, IPoolableObject* const);

protected:
	UWorld* World;
	UClass* Class;
	TQueue<IPoolableObject*> Pool;

public:
	int32 Length;
	FOnPush OnPush;

	void Initialize(UWorld* const World, UClass* const Class, const int32 StartSize = 0)
	{
		check(World != nullptr || Class != nullptr);

		this->World = World;
		this->Class = Class;
		OnPush.Clear();
		OnPush.AddLambda([this](IPoolableObject* PoolableObj) { PoolableObj->SetSelfPool(this); });
		Empty();
		Grow(StartSize);
	}

	// Returns casted PoolableObject from pool, bShouldCreateNew defines if should spawn and return new object when pool is empty
	template<class T>
	FORCEINLINE T* Pop(const bool bShouldCreateNew = false)
	{
		return Cast<T>(Pop(bShouldCreateNew));
	}

	// Returns PoolableObject from pool, bShouldCreateNew defines if should spawn and return new object when pool is empty
	FORCEINLINE virtual IPoolableObject* Pop(const bool bShouldCreateNew = false)
	{
		IPoolableObject* Obj = nullptr;
		if (!Pool.Dequeue(Obj) && bShouldCreateNew)
		{
			return SpawnObject();
		}
		if (Obj != nullptr)
		{
			Obj->Enable();
		}
		return Obj;
	}

	FORCEINLINE void Push(IPoolableObject* PoolableObj)
	{
		OnPush.Broadcast(PoolableObj);
		PoolableObj->Disable();
		Pool.Enqueue(PoolableObj);
		Length++;
	}

	// Increase pool size with new spawned Actors (CreateNewobject())
	FORCEINLINE void Grow(int32 Size)
	{
		Length += Size;
		while (Size > 0)
		{
			Push(SpawnObject());
			Size--;
		}
	}

	// Empties pool, bDestroy defines if all Actors from pool should be destroyed
	FORCEINLINE void Empty(bool bDestroy = true)
	{
		if (bDestroy)
		{
			IPoolableObject* PoolableObj;
			while (Pool.Dequeue(PoolableObj))
			{
				PoolableObj->Kill();
			}
		}
		Pool.Empty();
		Length = 0;
	}

	FORCEINLINE virtual IPoolableObject* SpawnObject() { unimplemented(); return nullptr; }

};