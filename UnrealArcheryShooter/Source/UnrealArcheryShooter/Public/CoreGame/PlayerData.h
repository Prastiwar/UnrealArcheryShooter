// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "PlayerData.generated.h"

USTRUCT(BlueprintType)
struct UNREALARCHERYSHOOTER_API FPlayerData
{
	GENERATED_BODY()

public:
	FPlayerData() {}
	FPlayerData(const float Score) { this->Score = Score; }
	~FPlayerData() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Score = 1;
};
