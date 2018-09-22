// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "CoreMinimal.h"
#include "Queue.h"

template<typename InElementType>
class UNREALARCHERYSHOOTER_API TObjectPool
{
private:
	TQueue<InElementType> Pool;

public:
	typedef InElementType ElementType;
	int32 Length;

	FORCEINLINE TObjectPool(const ElementType* Ptr, int32 Count)
	{
		check(Ptr != nullptr || Count == 0);
		Pool = TQueue<InElementType>();
		Length = 0;
	}

	FORCEINLINE InElementType* Get()
	{
		InElementType* Obj = nullptr;
		if (Pool.Dequeue(Obj))
		{
			return Obj;
		}
		return CreateNewObject();
	}
	
	void Push(InElementType* Obj)
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
	virtual void OnPush(InElementType* Obj);
	abstract InElementType* CreateNewObject();
};