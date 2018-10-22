// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "BTService_TrackLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"

UBTService_TrackLocation::UBTService_TrackLocation()
{
}

void UBTService_TrackLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	for (FActorLocationPair& Pair : TrackActorLocations)
	{
		AActor* Actor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(Pair.ActorKey.SelectedKeyName));
		if (Actor)
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsVector(Pair.VectorKey.SelectedKeyName, Actor->GetActorLocation());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Cant resolve ActorKey from BTService_TrackLocation"));
		}
	}
}

void UBTService_TrackLocation::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);

	UBlackboardData* BBAsset = GetBlackboardAsset();
	if (ensure(BBAsset))
	{
		for (FActorLocationPair& Pair : TrackActorLocations)
		{
			Pair.ActorKey.ResolveSelectedKey(*BBAsset);
			Pair.VectorKey.ResolveSelectedKey(*BBAsset);
		}
	}
}