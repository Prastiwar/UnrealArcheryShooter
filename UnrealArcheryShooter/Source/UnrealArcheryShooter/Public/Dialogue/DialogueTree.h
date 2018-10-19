// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "Dialogue/DialogueNode.h"
#include "DialogueTree.generated.h"

UCLASS(Blueprintable, BlueprintType)
class UNREALARCHERYSHOOTER_API UDialogueTree : public UObject
{
	GENERATED_BODY()

public:
	UDialogueTree();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<FDialogueNode> Nodes;

};
