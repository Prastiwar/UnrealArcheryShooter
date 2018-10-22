// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Wander.generated.h"

UCLASS()
class UNREALARCHERYSHOOTER_API UBTTask_Wander : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_Wander();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	FVector RandomTargetLocation;
	bool bIsMoveCompleted = true;

	UPROPERTY(EditAnywhere)
		float WanderRadius;

	UPROPERTY(EditAnywhere)
		float AcceptanceRadius;

	// Cached AIController owner of BehaviorTreeComponent
	UPROPERTY(Transient)
		class AAIController* AIOwner;

	// Cached actor owner of BehaviorTreeComponent
	UPROPERTY(Transient)
		AActor* ActorOwner;

	// Cached UBehaviorTreeComponent
	UPROPERTY(Transient)
		UBehaviorTreeComponent* OwnerComp;

	void CompleteMove(struct FAIRequestID RequestID, const struct FPathFollowingResult& Result);
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void SetOwner(AActor* OwnerActor) override;

	virtual void OnGameplayTaskDeactivated(class UGameplayTask& Task) { Super::OnGameplayTaskDeactivated(Task); }
	virtual void OnGameplayTaskActivated(class UGameplayTask& Task) { Super::OnGameplayTaskActivated(Task); }

};
