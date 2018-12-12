// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "FloatingActorComponent.h"

UFloatingActorComponent::UFloatingActorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	TimeScale = 1.0f;
}

void UFloatingActorComponent::BeginPlay()
{
	Super::BeginPlay();
	if (!Target)
	{
		SetTarget(GetOwner());
	}
}

void UFloatingActorComponent::SetTarget(AActor* const NewTarget)
{
	if (NewTarget)
	{
		Target = NewTarget;
		Target->GetRootComponent()->SetMobility(EComponentMobility::Movable);
		InitLocation = Target->GetActorLocation();
		TargetLocation = InitLocation + DirectionOffset;
		bIsReversed = false;
		Position = 0.0f;
	}
}

void UFloatingActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	Position += DeltaTime * TimeScale;

	const bool bReached = Position >= 1.0f;
	const float InterpValue = GetCurveFloatValue(bReached ? 1.0f : Position);
	Interp(InterpValue);

	if (bReached)
	{
		bIsReversed = !bIsReversed;
		Position = 0.0f;
		if (OnDirectionChanged.IsBound())
		{
			OnDirectionChanged.Broadcast(bIsReversed);
		}
	}
}

float UFloatingActorComponent::GetCurveFloatValue(float InTime)
{
	if (BackCurveFloat)
	{
		return bIsReversed
			? BackCurveFloat->GetFloatValue(InTime)
			: CurveFloat->GetFloatValue(InTime);
	}
	else
	{
		return bIsReversed
			? CurveFloat->GetFloatValue(1 - InTime)
			: CurveFloat->GetFloatValue(InTime);
	}
}

void UFloatingActorComponent::Interp(float Value)
{
	const FVector NewLocation = FMath::Lerp(InitLocation, TargetLocation, Value);
	Target->SetActorLocation(NewLocation);
}
