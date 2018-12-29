// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "ElevatorActor.h"
#include "FloatingActorComponent.h"

AElevatorActor::AElevatorActor()
{
	ActivateLiftDelay = 1.0f;

	LeverMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeverMesh"));

	FloatingComp = CreateDefaultSubobject<UFloatingActorComponent>(TEXT("FloatingComp"));
	FloatingComp->OnDirectionChanged.AddDynamic(this, &AElevatorActor::OnFloatingDirectionChanged);

	// TODO: Changeable shape
	TriggerShape = Cast<UShapeComponent>(CreateDefaultSubobject<UTriggerBoxComponent>(TEXT("TriggerShape")));
	if (ITrigger* Trigger = Cast<ITrigger>(TriggerShape))
	{
		Trigger->BindTrigger(this, &AElevatorActor::OnTrigger, nullptr);
	}
}

void AElevatorActor::BeginPlay()
{
	Super::BeginPlay();
	FloatingComp->SetComponentTickEnabled(false);
}

void AElevatorActor::OnTrigger(AActor* OtherActor, UPrimitiveComponent* OtherComp)
{
	FTimerHandle Handle;
	FTimerDelegate Del;
	Del.BindLambda([=]() { FloatingComp->SetComponentTickEnabled(true); });
	GetWorld()->GetTimerManager().SetTimer(Handle, Del, 1, false, ActivateLiftDelay);
}

void AElevatorActor::OnFloatingDirectionChanged(const bool bIsReversed)
{
	FloatingComp->SetComponentTickEnabled(false);
}
