// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "QuestData.generated.h"

USTRUCT(BlueprintType)
struct UNREALARCHERYSHOOTER_API FQuestData
{
	GENERATED_BODY()

public:
	FQuestData() {}
	~FQuestData() {}

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 ID;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly)
		//class AQuestGiver* QuestGiver;

	FORCEINLINE bool operator==(const FQuestData &Other) const { return ID == Other.ID; }
	FORCEINLINE bool operator!=(const FQuestData &Other) const { return !(ID == Other.ID); }

	friend uint32 GetTypeHash(const FQuestData& Other)
	{
		return GetTypeHash(Other.ID);
	}

};
