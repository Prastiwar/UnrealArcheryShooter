// // Copyright 2018-2019 Tomasz Piowczyk, MIT License

#pragma once

#include "CoreMinimal.h"
#include "SpawnData.generated.h"

USTRUCT()
struct CPPLEARN_API FSpawnData
{
	GENERATED_BODY()

public:
	FSpawnData();
	FSpawnData(FLinearColor Color, float Score);
	~FSpawnData();

	UPROPERTY(VisibleAnywhere)
		FLinearColor Color;
	UPROPERTY(VisibleAnywhere)
		float Score;
};
