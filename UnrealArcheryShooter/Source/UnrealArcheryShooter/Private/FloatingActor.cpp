// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "FloatingActor.h"
#include "TPMath.h"
#include "CoreMinimal.h"

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
	float Time = FTPMath::PingPong(EvaluateTime, 1.0f);
	float EvaluatedAlpha = CurveFloat->GetFloatValue(Time);
	FVector NewLocation = FMath::Lerp(InitLocation, TargetLocation, EvaluatedAlpha);
	SetActorLocation(NewLocation);
}
