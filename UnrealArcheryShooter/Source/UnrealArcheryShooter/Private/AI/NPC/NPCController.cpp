// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "NPCController.h"
#include "NPC/NPC.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BehaviorTreeComponent.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BehaviorTree.h"

ANPCController::ANPCController()
{
	BehaviourComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviourComp"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
}

void ANPCController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);

	if (ANPC* NPC = Cast<ANPC>(InPawn))
	{
		if (NPC->BehaviourTree->BlackboardAsset)
		{
			BlackboardComp->InitializeBlackboard(*NPC->BehaviourTree->BlackboardAsset);
		}

		BehaviourComp->StartTree(*NPC->BehaviourTree);
	}
}
