 // Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "PoolableObject.h"
#include "ObjectPool.h"

bool IPoolableObject::ReturnToSelfPool()
{
	bool HasSelfPool = SelfPool;
	if (HasSelfPool)
	{
		SelfPool->Push(this);
	}
	return HasSelfPool;
}