// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "CooldownData.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FMDFloatValueChanged, float);

USTRUCT(BlueprintType)
struct UNREALARCHERYSHOOTER_API FCooldownData
{
	GENERATED_BODY()

public:
	FCooldownData() {}
	~FCooldownData() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float TickRateMultiplier = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float InitialTime = 1.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float CooldownTime = 1.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool bIsCompleted = true;

	FMDFloatValueChanged OnValueChanged;
	int32 ID;

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
