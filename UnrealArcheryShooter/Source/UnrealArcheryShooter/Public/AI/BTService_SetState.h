// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BehaviorTree/BTDecorator.h"
#include "BehaviorTree/BTNode.h"
#include "BTService_SetState.generated.h"

UCLASS()
class UNREALARCHERYSHOOTER_API UBTService_SetState : public UBTService
{
	GENERATED_BODY()
	
public:
	UBTService_SetState();

	UPROPERTY(EditAnywhere)
		UEnum* Enumeration;

	UPROPERTY(EditAnywhere)
		UBTNode* NodeWithDecoratChecks;

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	virtual void OnGameplayTaskDeactivated(class UGameplayTask& Task) { Super::OnGameplayTaskDeactivated(Task); }
	virtual void OnGameplayTaskActivated(class UGameplayTask& Task) { Super::OnGameplayTaskActivated(Task); }
	
};
