// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "Engine.h"
#include "Queue.h"

template<typename ObjectType>
class UNREALARCHERYSHOOTER_API TObjectPool
{
protected:
	TQueue<ObjectType> Pool;
	ObjectType* Ptr;
	UWorld* World;

public:
	int32 Length;

	TObjectPool(const UWorld* World, const ObjectType* Ptr, const int32 Count)
	{
		check(Ptr != nullptr || Count == 0);
		Pool = TQueue<ObjectType>();
		Length = 0;
		this->Ptr = Ptr;
		this->World = World;
	}

	virtual ~TObjectPool()
	{
		Pool->~TQueue();
	}

	FORCEINLINE ObjectType* Get()
	{
		ObjectType* Obj = nullptr;
		if (Pool.Dequeue(Obj))
		{
			return Obj;
		}
		return CreateNewObject();
	}
	
	FORCEINLINE void Push(ObjectType* Obj)
	{
		OnPush(Obj);
		Pool.Enqueue(Obj);
		Length++;
	}
	
	FORCEINLINE void Grow(const int Size)
	{
		for (int i = 0; i < Size; i++)
		{
			Push(CreateNewObject());
		}
	}

	FORCEINLINE void Empty()
	{
		Pool.Empty();
		Length = 0;
	}

protected:
	virtual void OnPush(ObjectType* Obj)
	{
		unimplemented();
	}

	virtual ObjectType* CreateNewObject()
	{
		unimplemented();
		return nullptr;
	}
};