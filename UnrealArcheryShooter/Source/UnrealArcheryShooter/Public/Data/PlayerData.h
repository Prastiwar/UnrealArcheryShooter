// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "CoreMinimal.h"
#include "PlayerData.generated.h"

USTRUCT()
struct UNREALARCHERYSHOOTER_API FPlayerData
{
	GENERATED_BODY()

public:
	FPlayerData();
	~FPlayerData();

	UPROPERTY(EditAnywhere)
		float Score;
};
