// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "CoreMinimal.h"
#include "CooldownData.generated.h"

USTRUCT()
struct UNREALARCHERYSHOOTER_API FCooldownData
{
	GENERATED_BODY()

public:
	FCooldownData() { }
	~FCooldownData() { }

	int ID = 0;

	UPROPERTY(EditAnywhere)
		float TickRateMultiplier = 1.0f;

	UPROPERTY(EditAnywhere)
		float InitialTime = 1.0f;

	UPROPERTY(VisibleAnywhere)
		float CooldownTime = 1.0f;

	UPROPERTY(VisibleAnywhere)
		bool bIsCompleted = true;

	FORCEINLINE bool operator==(const FCooldownData &Other) const { return ID == Other.ID; }
	FORCEINLINE bool operator!=(const FCooldownData &Other) const { return !(ID == Other.ID); }
	
	friend uint32 GetTypeHash(const FCooldownData& Other)
	{
		return GetTypeHash(Other.ID)
			+ GetTypeHash(Other.TickRateMultiplier)
			+ GetTypeHash(Other.InitialTime)
			+ GetTypeHash(Other.CooldownTime)
			+ GetTypeHash(Other.bIsCompleted);
	}
};
