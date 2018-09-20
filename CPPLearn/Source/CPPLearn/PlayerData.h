// // Copyright 2018-2019 Tomasz Piowczyk, MIT License

#pragma once

#include "CoreMinimal.h"
#include "PlayerData.generated.h"

USTRUCT()
struct CPPLEARN_API FPlayerData
{
	GENERATED_BODY()

public:
	FPlayerData();
	~FPlayerData();

	UPROPERTY(EditAnywhere)
		float Score;
};
