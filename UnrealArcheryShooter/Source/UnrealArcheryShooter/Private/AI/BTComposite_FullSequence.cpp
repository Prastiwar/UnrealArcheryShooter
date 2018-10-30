// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "BTComposite_FullSequence.h"

UBTComposite_FullSequence::UBTComposite_FullSequence(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "FullSequence";
	OnNextChild.BindUObject(this, &UBTComposite_FullSequence::GetNextChildHandler);
}

int32 UBTComposite_FullSequence::GetNextChildHandler(FBehaviorTreeSearchData& SearchData, int32 PrevChild, EBTNodeResult::Type LastResult) const
{
	if (PrevChild == BTSpecialChild::NotInitialized)
	{
		return 0; // newly activated: start from first
	}
	else if (PrevChild < GetChildrenNum() - 1)
	{
		return PrevChild + 1;
	}
	return BTSpecialChild::ReturnToParent; // failure - quit
}
