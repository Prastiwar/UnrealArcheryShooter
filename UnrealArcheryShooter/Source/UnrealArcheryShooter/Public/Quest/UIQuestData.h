// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "Engine/DataTable.h"
#include "Quest/QuestData.h"
#include "UIQuestData.generated.h"

USTRUCT(BlueprintType)
struct UNREALARCHERYSHOOTER_API FUIQuestData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FUIQuestData() {}
	~FUIQuestData() {}

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FQuestData QuestData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Description;

};
