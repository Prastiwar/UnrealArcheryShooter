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
		bool IsCompleted = true;

	FORCEINLINE bool operator==(const FCooldownData &Other) const { return ID == Other.ID; }
	FORCEINLINE bool operator!=(const FCooldownData &Other) const { return ID == Other.ID; }
};
