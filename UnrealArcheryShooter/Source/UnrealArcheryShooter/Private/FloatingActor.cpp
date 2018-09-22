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
	TimeScale = 1.0f;
	EvaluateTime = 0;
}

void AFloatingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Weird unreal bug - function doesnt work only in update functions
	// EvaluateTime = FTPMath::PingPong(EvaluateTime + DeltaTime * TimeScale, 1.0f);

	EvaluateTime = FTPMath::Repeat(EvaluateTime + DeltaTime * TimeScale, 1.0f);

	float EvaluatedAlpha = CurveFloat->GetFloatValue(EvaluateTime);
	FVector NewLocation = FMath::Lerp(InitLocation, TargetLocation, EvaluatedAlpha);
	SetActorLocation(NewLocation);
}
