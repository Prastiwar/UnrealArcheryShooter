// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "BTTask_Wander.h"
#include "AIController.h"
#include "NavigationSystem.h"

UBTTask_Wander::UBTTask_Wander()
{
	WanderRadius = 1000.0f;
	AcceptanceRadius = 10.0f;
	bIsMoveCompleted = true;
}

EBTNodeResult::Type UBTTask_Wander::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (!ActorOwner)
	{
		this->OwnerComp = &OwnerComp;
		SetOwner(this->OwnerComp->GetOwner());
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

EBTNodeResult::Type UBTTask_Wander::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UE_LOG(LogTemp, Warning, TEXT("Hey"));
	return EBTNodeResult::Failed;
}

void UBTTask_Wander::SetOwner(AActor* OwnerActor)
{
	this->ActorOwner = OwnerActor;
	this->AIOwner = Cast<AAIController>(OwnerActor);
}
