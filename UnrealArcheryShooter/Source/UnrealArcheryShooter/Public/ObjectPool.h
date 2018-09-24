// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "CoreMinimal.h"
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

	TObjectPool(const UWorld* World, const ObjectType* Ptr, int32 Count)
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

	ObjectType* Get()
	{
		ObjectType* Obj = nullptr;
		if (Pool.Dequeue(Obj))
		{
			return Obj;
		}
		return CreateNewObject();
	}
	
	void Push(ObjectType* Obj)
	{
		OnPush(Obj);
		Pool.Enqueue(Obj);
		Length++;
	}
	
	void Grow(const int Size)
	{
		for (int i = 0; i < Size; i++)
		{
			Push(CreateNewObject());
		}
	}

	void Empty()
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