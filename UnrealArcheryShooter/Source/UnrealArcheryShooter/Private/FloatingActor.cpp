// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "FloatingActor.h"

AFloatingActor::AFloatingActor()
{
	PrimaryActorTick.bCanEverTick = true;
	TimeScale = 1.0f;
	SetMobility(EComponentMobility::Movable);
}

void AFloatingActor::BeginPlay()
{
	Super::BeginPlay();
	InitLocation = GetActorLocation();
	TargetLocation = InitLocation + DirectionOffset;
}

void AFloatingActor::Tick(float DeltaTime)
{
	Position += DeltaTime * TimeScale;

	const bool bReached = Position >= 1.0f;
	const float InterpValue = GetCurveFloatValue(bReached ? 1.0f : Position);
	Interp(InterpValue);

	if (bReached)
	{
		bIsReversed = !bIsReversed;
		Position = 0.0f;
	}
}

float AFloatingActor::GetCurveFloatValue(float InTime)
{
	if (BackCurveFloat)
	{
		return bIsReversed
			? CurveFloat->GetFloatValue(InTime)
			: BackCurveFloat->GetFloatValue(InTime);
	}
	else
	{
		return bIsReversed
			? CurveFloat->GetFloatValue(InTime)
			: CurveFloat->GetFloatValue(1 - InTime);
	}
}

void AFloatingActor::Interp(float Value)
{
	const FVector NewLocation = FMath::Lerp(InitLocation, TargetLocation, Value);
	SetActorLocation(NewLocation);
}
