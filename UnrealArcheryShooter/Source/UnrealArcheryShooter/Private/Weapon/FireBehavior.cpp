// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "FireBehavior.h"
#include "TPMeasure/TPMeasure.h"
#include "DrawDebugHelpers.h"

UFireBehavior::UFireBehavior()
{
	ExplodeHitRadius = 10.0f;
	ExplodeHitRadialStrength = 500.0f;
	FireCost = 20.0f;
	FireRange = 10000.0f;
	PrecisionOffset = FVector(0.0f, 0.0f, 0.0f);
}

void UFireBehavior::Fire(AActor* Outer, const FVector Start, const FVector Forward)
{
	CallerPrivate = Outer;
	WorldPrivate = Outer->GetWorld();
	OnFire(Start, Forward);
}

void UFireBehavior::OnFire_Implementation(const FVector Start, const FVector Forward)
{
	FHitResult OutHit;
	FVector End = ((Forward * FireRange) + Start) + PrecisionOffset;
	FCollisionQueryParams CollisionParams;

	const bool bTraceHit = WorldPrivate->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility, CollisionParams);
	DrawDebugLine(WorldPrivate, Start, bTraceHit ? OutHit.ImpactPoint : End, FColor::Red, false, 2.0f);
	DrawDebugPoint(WorldPrivate, bTraceHit ? OutHit.ImpactPoint : End, 16.0f, FColor::Red, false, 2.0f);

	UParticleSystemComponent* ParticleComp =
		UGameplayStatics::SpawnEmitterAtLocation(WorldPrivate, BeamParticle, Start, FRotator::ZeroRotator, FVector(1.f), true, EPSCPoolMethod::None);
	if (ParticleComp)
	{
		ParticleComp->SetBeamSourcePoint(0, Start, 0);
		ParticleComp->SetBeamTargetPoint(0, bTraceHit ? OutHit.ImpactPoint : End, 0);
	}

	// HACKY BUG FIX - Beam loop ue4 4.20 bug, can't pool it
	FTimerDelegate LifeTimeDel = FTimerDelegate();
	FTimerHandle ParticleLifetimeHandle;
	LifeTimeDel.BindLambda([=]() { ParticleComp->DestroyComponent(); });
	WorldPrivate->GetTimerManager().SetTimer(ParticleLifetimeHandle, LifeTimeDel, 1, false, ParticleLifetime);

	if (bTraceHit && OutHit.bBlockingHit)
	{
		OnHit(OutHit.GetActor(), OutHit.GetComponent(), OutHit);
	}
	else
	{
		OnMissHit();
	}
}
