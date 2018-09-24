// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "CoreMinimal.h"
#include "SpawnData.generated.h"

USTRUCT()
struct UNREALARCHERYSHOOTER_API FSpawnData
{
	GENERATED_BODY()

public:
	FSpawnData() { }
	FSpawnData(FLinearColor Color, float Score) 
	{
		this->Color = Color;
		this->Score = Score;
	}

	~FSpawnData() { }

	UPROPERTY(EditAnywhere)
		FLinearColor Color;

	UPROPERTY(EditAnywhere)
		float Score = 1;
};
