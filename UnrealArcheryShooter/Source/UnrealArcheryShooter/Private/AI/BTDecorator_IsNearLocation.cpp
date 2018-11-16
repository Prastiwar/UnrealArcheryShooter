// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "BTDecorator_IsNearLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"

UBTDecorator_IsNearLocation::UBTDecorator_IsNearLocation()
{
	NodeName = "Is Near Location";

	CheckLocationKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTDecorator_IsNearLocation, CheckLocationKey), AActor::StaticClass());
	CheckLocationKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTDecorator_IsNearLocation, CheckLocationKey));

	TargetLocationKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTDecorator_IsNearLocation, TargetLocationKey), AActor::StaticClass());
	TargetLocationKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTDecorator_IsNearLocation, TargetLocationKey));
}

void UBTDecorator_IsNearLocation::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);

	UBlackboardData* BBAsset = GetBlackboardAsset();
	if (ensure(BBAsset))
	{
		CheckLocationKey.ResolveSelectedKey(*BBAsset);
		TargetLocationKey.ResolveSelectedKey(*BBAsset);
	}
	SetIsNearLocationCalculation();
}

void UBTDecorator_IsNearLocation::SetIsNearLocationCalculation()
{
	if (TargetLocationKey.SelectedKeyType == UBlackboardKeyType_Object::StaticClass())
	{
		if (CheckLocationKey.SelectedKeyType == UBlackboardKeyType_Object::StaticClass())
		{
			OnCalculate.BindLambda([this](const UBlackboardComponent* BlackboardComp) {
				AActor* TargetActor = Cast<AActor>(BlackboardComp->GetValue<UBlackboardKeyType_Object>(TargetLocationKey.GetSelectedKeyID()));
				AActor* CheckActor = Cast<AActor>(BlackboardComp->GetValue<UBlackboardKeyType_Object>(CheckLocationKey.GetSelectedKeyID()));
				return IsNearLocation(CheckActor, TargetActor);
			});
		}
		else if (CheckLocationKey.SelectedKeyType == UBlackboardKeyType_Vector::StaticClass())
		{
			OnCalculate.BindLambda([this](const UBlackboardComponent* BlackboardComp) {
				AActor* TargetActor = Cast<AActor>(BlackboardComp->GetValue<UBlackboardKeyType_Object>(TargetLocationKey.GetSelectedKeyID()));
				const FVector CheckLocation = BlackboardComp->GetValue<UBlackboardKeyType_Vector>(CheckLocationKey.GetSelectedKeyID());
				return IsNearLocation(CheckLocation, TargetActor);
			});
		}
	}
	else if (TargetLocationKey.SelectedKeyType == UBlackboardKeyType_Vector::StaticClass())
	{
		if (CheckLocationKey.SelectedKeyType == UBlackboardKeyType_Object::StaticClass())
		{
			OnCalculate.BindLambda([this](const UBlackboardComponent* BlackboardComp) {
				const FVector TargetLocation = BlackboardComp->GetValue<UBlackboardKeyType_Vector>(TargetLocationKey.GetSelectedKeyID());
				AActor* CheckActor = Cast<AActor>(BlackboardComp->GetValue<UBlackboardKeyType_Object>(CheckLocationKey.GetSelectedKeyID()));
				return IsNearLocation(CheckActor, TargetLocation);
			});
		}
		else if (CheckLocationKey.SelectedKeyType == UBlackboardKeyType_Vector::StaticClass())
		{
			OnCalculate.BindLambda([this](const UBlackboardComponent* BlackboardComp) {
				const FVector TargetLocation = BlackboardComp->GetValue<UBlackboardKeyType_Vector>(TargetLocationKey.GetSelectedKeyID());
				const FVector CheckLocation = BlackboardComp->GetValue<UBlackboardKeyType_Vector>(CheckLocationKey.GetSelectedKeyID());
				return IsNearLocation(CheckLocation, TargetLocation);
			});
		}
	}
	else
	{
		OnCalculate.BindLambda([this](const UBlackboardComponent* BlackboardComp) {
			return false;
		});
	}
}

bool UBTDecorator_IsNearLocation::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	return OnCalculate.Execute(BlackboardComp);
}

bool UBTDecorator_IsNearLocation::IsNearLocation(const FVector& A, const FVector& B) const
{
	return GetGeometricDistanceSquared(A, B) < FMath::Square(AcceptableRadius);
}

bool UBTDecorator_IsNearLocation::IsNearLocation(const AActor* A, const FVector& B) const
{
	return A
		? GetGeometricDistanceSquared(A->GetActorLocation(), B) < FMath::Square(AcceptableRadius)
		: false;
}

bool UBTDecorator_IsNearLocation::IsNearLocation(const FVector& A, const AActor* B) const
{
	return B
		? GetGeometricDistanceSquared(A, B->GetActorLocation()) < FMath::Square(AcceptableRadius)
		: false;
}

bool UBTDecorator_IsNearLocation::IsNearLocation(const AActor* A, const AActor* B) const
{
	return A && B
		? GetGeometricDistanceSquared(A->GetActorLocation(), B->GetActorLocation()) < FMath::Square(AcceptableRadius)
		: false;
}

float UBTDecorator_IsNearLocation::GetGeometricDistanceSquared(const FVector& A, const FVector& B) const
{
	float Result = MAX_flt;
	switch (GeometricDistanceType)
	{
		case FAIDistanceType::Distance3D:
			Result = FVector::DistSquared(A, B);
			break;
		case FAIDistanceType::Distance2D:
			Result = FVector::DistSquaredXY(A, B);
			break;
		case FAIDistanceType::DistanceZ:
			Result = FMath::Square(A.Z - B.Z);
			break;
		default:
			checkNoEntry();
			break;
	}
	return Result;
}
