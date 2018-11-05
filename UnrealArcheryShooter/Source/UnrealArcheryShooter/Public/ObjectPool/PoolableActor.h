// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "GameFramework/Actor.h"
#include "ActorHelper.h"
#include "PoolableObject.h"
#include "PoolableActor.generated.h"

UCLASS()
class UNREALARCHERYSHOOTER_API APoolableActor : public AActor, public IPoolableObject
{
	GENERATED_BODY()

public:
	/** How long this Actor lives before dying(disabling), 0 = forever. Note this is the INITIAL value and should not be modified once play has begun. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Actor)
		float InitialLifeSpanPooled;

	virtual void Enable() override
	{
		FActorHelper::SetActive(this, true);
		SetLifeSpanPooled(InitialLifeSpanPooled);
	}

	virtual void Kill() override
	{
		Destroy();
	}

	virtual void Disable()
	{
		FActorHelper::SetActive(this, false);
	}

	void SetLifeSpanPooled(const float InLifespan)
	{
		InitialLifeSpanPooled = InLifespan;

		if ((Role == ROLE_Authority || GetTearOff()) && !IsPendingKill())
		{
			if (InLifespan > 0.0f)
			{
				GetWorldTimerManager().SetTimer(LifeSpanTimer, this, &APoolableActor::Disable, InLifespan);
			}
			else
			{
				GetWorldTimerManager().ClearTimer(LifeSpanTimer);
			}
		}
	}

	float GetLifeSpanPooled() const
	{
		// Timer remaining returns -1.0f if there is no such timer - return this as ZERO
		const float CurrentLifespan = GetWorldTimerManager().GetTimerRemaining(TimerHandle_LifeSpanExpired);
		return (CurrentLifespan != -1.0f) ? CurrentLifespan : 0.0f;
	}

private:
	FTimerHandle LifeSpanTimer;

};