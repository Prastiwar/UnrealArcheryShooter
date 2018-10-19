// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "BoostData.generated.h"

USTRUCT(BlueprintType)
struct UNREALARCHERYSHOOTER_API FBoostData
{
	GENERATED_BODY()

public:
	FBoostData() {}
	FBoostData(const float Power, const float TimeLast)
	{
		this->Power = Power;
		this->TimeLast = TimeLast;
	}

	~FBoostData() {}

	UPROPERTY(VisibleAnywhere)
		AActor* AppliedActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Power = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float TimeLast = 1;

	FTimerHandle TimerHandle;

};
