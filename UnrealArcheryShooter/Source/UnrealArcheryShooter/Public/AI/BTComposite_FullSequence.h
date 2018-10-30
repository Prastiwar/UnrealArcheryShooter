// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "BehaviorTree/BTCompositeNode.h"
#include "BTComposite_FullSequence.generated.h"

/**
 * Full Sequence composite node.
 * Sequence Nodes execute their children from left to right, and will NOT stop executing its children when one of their children fails.
 */
UCLASS()
class UNREALARCHERYSHOOTER_API UBTComposite_FullSequence : public UBTCompositeNode
{
	GENERATED_BODY()

public:
	UBTComposite_FullSequence(const FObjectInitializer& ObjectInitializer);

	int32 GetNextChildHandler(struct FBehaviorTreeSearchData& SearchData, int32 PrevChild, EBTNodeResult::Type LastResult) const;

	virtual void OnGameplayTaskDeactivated(class UGameplayTask& Task) { Super::OnGameplayTaskDeactivated(Task); }
	virtual void OnGameplayTaskActivated(class UGameplayTask& Task) { Super::OnGameplayTaskActivated(Task); }

};
