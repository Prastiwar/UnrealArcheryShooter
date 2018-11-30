// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "FireBehavior.h"

UFireBehavior::UFireBehavior()
{
	ExplodeHitRadius = 10.0f;
	ExplodeHitRadialStrength = 500.0f;
	FireCost = 20.0f;
	FireRange = 10000.0f;
}

void UFireBehavior::Fire_Implementation(const UWorld* World, const FVector Start, const FVector Forward)
{
	FHitResult OutHit;
	FVector End = ((Forward * FireRange) + Start);
	FCollisionQueryParams CollisionParams;

	const bool bTraceHit = World->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility, CollisionParams);
	if (bTraceHit && OutHit.bBlockingHit)
	{
		OnHit(OutHit.GetActor(), OutHit.GetComponent(), OutHit);
	}

	UParticleSystemComponent* ParticleComp =
		UGameplayStatics::SpawnEmitterAtLocation(World, BeamParticle, Start, FRotator::ZeroRotator, FVector(1.f), true, EPSCPoolMethod::AutoRelease);
	ParticleComp->SetBeamSourcePoint(0, Start, 0);
	ParticleComp->SetBeamTargetPoint(0, End, 0);
}
