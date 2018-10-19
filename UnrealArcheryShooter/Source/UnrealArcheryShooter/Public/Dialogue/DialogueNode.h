// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "Dialogue/DialogueOption.h"
#include "DialogueNode.generated.h"

USTRUCT(BlueprintType)
struct UNREALARCHERYSHOOTER_API FDialogueNode
{
	GENERATED_BODY()

public:
	FDialogueNode() {}
	~FDialogueNode() {}

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Text;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FDialogueOption> DialogueOptions;

	FORCEINLINE bool operator==(const FDialogueNode &Other) const { return ID == Other.ID; }
	FORCEINLINE bool operator!=(const FDialogueNode &Other) const { return !(ID == Other.ID); }

};
