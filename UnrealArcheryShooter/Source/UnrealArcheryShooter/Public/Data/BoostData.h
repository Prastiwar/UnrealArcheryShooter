// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "Engine.h"
#include "BoostData.generated.h"

USTRUCT()
struct UNREALARCHERYSHOOTER_API FBoostData
{
	GENERATED_BODY()

public:
	FBoostData() { }
	FBoostData(float Power, float TimeLast)
	{
		this->Power = Power;
		this->TimeLast = TimeLast;
	}

	~FBoostData() { }

	FTimerHandle TimerHandle;

	UPROPERTY(VisibleAnywhere)
		AActor* AppliedActor;

	UPROPERTY(EditAnywhere)
		float Power = 1;

	UPROPERTY(EditAnywhere)
		float TimeLast = 1;

};
