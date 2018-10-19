// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "DialogueOption.generated.h"

USTRUCT(BlueprintType)
struct UNREALARCHERYSHOOTER_API FDialogueOption
{
	GENERATED_BODY()

public:
	FDialogueOption() {}
	~FDialogueOption() {}

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Text;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	struct FDialogueNode* NextNode;

	FORCEINLINE bool operator==(const FDialogueOption &Other) const { return ID == Other.ID; }
	FORCEINLINE bool operator!=(const FDialogueOption &Other) const { return !(ID == Other.ID); }

};
