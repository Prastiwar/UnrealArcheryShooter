 // Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "UObject/Interface.h"
#include "PoolableObject.generated.h"

class IObjectPool;

UINTERFACE()
class UPoolableObject : public UInterface
{
	GENERATED_BODY()
};

class IPoolableObject
{
	GENERATED_BODY()

public:
	virtual void Enable() {}

	virtual void Kill() {}

	virtual void Disable() {}

	bool ReturnToSelfPool();

	FORCEINLINE void SetSelfPool(IObjectPool* Pool) { SelfPool = Pool; }

protected:
	IObjectPool* SelfPool;

};