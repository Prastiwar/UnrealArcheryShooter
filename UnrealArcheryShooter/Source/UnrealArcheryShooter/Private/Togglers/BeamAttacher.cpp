// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "BeamAttacher.h"
#include "UASCharacter.h"

ABeamAttacher::ABeamAttacher()
{
	PrimaryActorTick.bCanEverTick = true;
	BeamParticle = CreateDefaultSubobject<UParticleSystemComponent>("BeamParticle");
	UpdateRate = 0.1f;	
}

void ABeamAttacher::BeginPlay()
{
	Super::BeginPlay();
}

void ABeamAttacher::Activated(bool bActive, AActor* OverlappedActor)
{
	if (Cast<AUASCharacter>(OverlappedActor))
	{
		AttachedActor = OverlappedActor;
		if (bActive)
		{
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ABeamAttacher::AttachBeam, UpdateRate, true, 0.0f);
		}
		else
		{
			GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		}
	}
}

void ABeamAttacher::AttachBeam()
{
	//BeamParticle->SetBeamTargetPoint(0, AttachedActor->GetActorLocation() + AttachOffset, 0);
	BeamParticle->SetBeamTargetPoint(0, AttachedActor->GetActorLocation() + AttachOffset, 0);
}

void ABeamAttacher::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
