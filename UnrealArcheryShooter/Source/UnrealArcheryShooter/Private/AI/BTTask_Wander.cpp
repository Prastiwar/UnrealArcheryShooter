// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "BTTask_Wander.h"
#include "NavigationSystem.h"

EBTNodeResult::Type UBTTask_Wander::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (!ActorOwner)
	{
		this->OwnerComp = &OwnerComp;
		SetOwner(OwnerComp.GetAIOwner());
		AIOwner->GetPathFollowingComponent()->OnRequestFinished.AddUObject(this, &UBTTask_Wander::CompleteMove);
	}

	UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	FNavLocation ResultLocation;
	if (NavSystem->GetRandomPointInNavigableRadius(ActorOwner->GetActorLocation(), WanderRadius, ResultLocation))
	{
		bIsMoveCompleted = false;
		RandomTargetLocation = ResultLocation.Location;
		AIOwner->MoveToLocation(RandomTargetLocation, AcceptanceRadius);
	}
	return EBTNodeResult::InProgress;
}

void UBTTask_Wander::CompleteMove(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	bIsMoveCompleted = true;
	FinishLatentTask(*OwnerComp, EBTNodeResult::Succeeded);
}

void UBTTask_Wander::SetOwner(AActor* ActorOwner)
{
	this->ActorOwner = ActorOwner;
	this->AIOwner = Cast<AAIController>(ActorOwner);
}
