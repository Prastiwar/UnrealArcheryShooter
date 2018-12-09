// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "BeamAttacher.h"
#include "TriggerBoxComponent.h"
#include "Particles/ParticleSystemComponent.h"

ABeamAttacher::ABeamAttacher()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	// TODO: Changeable shape
	TriggerShape = Cast<UShapeComponent>(CreateDefaultSubobject<UTriggerBoxComponent>(TEXT("TriggerShape")));
	RootComponent = TriggerShape;
	if (ITrigger* Trigger = Cast<ITrigger>(TriggerShape))
	{
		Trigger->BindTrigger(this, &ABeamAttacher::TriggerToggle, &ABeamAttacher::TriggerToggle);
	}
	Toggle.OnToggled.BindUObject(this, &ABeamAttacher::Toggled);

	BeamParticle = CreateDefaultSubobject<UParticleSystemComponent>("BeamParticle");
	BeamParticle->SetupAttachment(TriggerShape);
}

void ABeamAttacher::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickEnabled(false);
}

void ABeamAttacher::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (AttachTarget)
	{
		AttachBeamToTarget(AttachTarget);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Attach Target found"));
	}
}

void ABeamAttacher::Toggled(const bool bActive)
{
	SetActorTickEnabled(bActive);
	SetActorHiddenInGame(!bActive);
}

void ABeamAttacher::TriggerToggle(AActor* OtherActor, UPrimitiveComponent* OtherComp)
{
	if (OtherActor->IsA(TargetClass.Get()))
	{
		AttachTarget = OtherActor;
		Toggle.Toggle();
	}
}

void ABeamAttacher::AttachBeamToTarget(AActor* Target)
{
	BeamParticle->SetBeamTargetPoint(0, Target->GetActorLocation() + AttachOffset, 0);
}
