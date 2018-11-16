// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_IsNearLocation.generated.h"

UCLASS()
class UNREALARCHERYSHOOTER_API UBTDecorator_IsNearLocation : public UBTDecorator
{
	GENERATED_BODY()
	DECLARE_DELEGATE_RetVal_OneParam(bool, FRawConditionValueCalculation, const UBlackboardComponent*)

public:
	UBTDecorator_IsNearLocation();

	// Will check if this key is near the TargetLocation
	UPROPERTY(EditAnywhere, Category = Blackboard)
		FBlackboardKeySelector CheckLocationKey;

	// The Location key to get to
	UPROPERTY(EditAnywhere, Category = Blackboard)
		FBlackboardKeySelector TargetLocationKey;

	// Distance threshold to accept as being at location
	UPROPERTY(EditAnywhere, Category = Condition, meta = (ClampMin = "0.0", EditCondition = "!bUseParametrizedRadius"))
		float AcceptableRadius;

	UPROPERTY(EditAnywhere, Category = Condition, meta = (EditCondition = "!bPathFindingBasedTest"))
		FAIDistanceType GeometricDistanceType;

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

protected:
	FRawConditionValueCalculation OnCalculate;

	float GetGeometricDistanceSquared(const FVector& A, const FVector& B) const;

	void SetIsNearLocationCalculation();

	bool IsNearLocation(const FVector& A, const FVector& B) const;
	bool IsNearLocation(const AActor* A, const FVector& B) const;
	bool IsNearLocation(const FVector& A, const AActor* B) const;
	bool IsNearLocation(const AActor* A, const AActor* B) const;

	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;

	virtual void OnGameplayTaskDeactivated(class UGameplayTask& Task) { Super::OnGameplayTaskDeactivated(Task); }
	virtual void OnGameplayTaskActivated(class UGameplayTask& Task) { Super::OnGameplayTaskActivated(Task); }
};
