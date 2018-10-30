// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/TPQuestPlugin

#include "ObjectiveBehavior.h"

UObjectiveBehavior::UObjectiveBehavior()
{
	CurrentProgress = 0;
	NeededProgress = 1;
	CurrentResult = EObjectiveResult::InProgress;
}

void UObjectiveBehavior::Begin()
{
	CurrentResult = EObjectiveResult::InProgress;
	ReceiveBegin();
}

void UObjectiveBehavior::Complete(const bool bSucceed)
{
	CurrentResult = bSucceed ? EObjectiveResult::Succeed : EObjectiveResult::Failed;
	CompleteImpl(bSucceed);
}

EObjectiveResult UObjectiveBehavior::Execute(UQuest* Owner, UQuestComponent* QuestOwner, float DeltaTime)
{
	ReceiveExecute(Owner, QuestOwner, DeltaTime);
	if (CurrentProgress >= NeededProgress && CurrentResult == EObjectiveResult::InProgress)
	{
		Complete(true);
	}
	return CurrentResult;
}
