// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "AIController.h"
#include "NPCController.generated.h"

UCLASS()
class UNREALARCHERYSHOOTER_API ANPCController : public AAIController
{
	GENERATED_BODY()
	
public:
	ANPCController();

	FORCEINLINE UBlackboardComponent* GetBlackboardComponent() const { return BlackboardComp; }

protected:
	class UBehaviorTreeComponent* BehaviourComp;

	class UBlackboardComponent* BlackboardComp;

	virtual void Possess(APawn* InPawn) override;
	
	
};
