// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "BeamAttacher.h"

ABeamAttacher::ABeamAttacher()
{
	PrimaryActorTick.bCanEverTick = true;
	BeamParticle = CreateDefaultSubobject<UParticleSystemComponent>("BeamParticle");
	UpdateRate = 0.016f;	
}

void ABeamAttacher::BeginPlay()
{
	Super::BeginPlay();
	Player = Cast<AUASCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
}

void ABeamAttacher::Activated(bool bActive, AActor* OverlappedActor)
{
	if (Cast<AUASCharacter>(OverlappedActor))
	{
		if (bActive)
		{
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ABeamAttacher::AttachBeam, UpdateRate, true);
		}
		else
		{
			GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		}
	}
}

void ABeamAttacher::AttachBeam()
{
	BeamParticle->SetBeamTargetPoint(0, Player->MuzzleLocation->GetComponentLocation() + AttachOffset, 0);
}
