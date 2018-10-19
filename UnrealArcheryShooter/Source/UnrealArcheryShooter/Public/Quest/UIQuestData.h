// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "UIQuestData.generated.h"

USTRUCT(BlueprintType)
struct UNREALARCHERYSHOOTER_API FUIQuestData
{
	GENERATED_BODY()

public:
	FUIQuestData() {}
	~FUIQuestData() {}

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		struct FQuestData QuestData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Description;

};
