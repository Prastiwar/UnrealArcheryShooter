// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "FloatingActor.h"
#include "TPMath.h"

AFloatingActor::AFloatingActor()
{
	PrimaryActorTick.bCanEverTick = true;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	TimeScale = 1.0f;
}

void AFloatingActor::BeginPlay()
{
	Super::BeginPlay();

	InitLocation = GetActorLocation();
	TargetLocation = InitLocation + FloatDirection; 
	EvaluateTime = 0;
}

void AFloatingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	EvaluateTime += DeltaTime * TimeScale;
	const float Time = FTPMath::PingPong(EvaluateTime, 1.0f);
	const float EvaluatedAlpha = CurveFloat->GetFloatValue(Time);
	const FVector NewLocation = FMath::Lerp(InitLocation, TargetLocation, EvaluatedAlpha);
	SetActorLocation(NewLocation);
}
