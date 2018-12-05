// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "UASFireBehavior.h"
#include "EngineUtils.h"
#include "DrawDebugHelpers.h"

bool UUASFireBehavior::TryAddScoreFromActor(AActor* OtherActor)
{
	if (ASpawnableRing* const ScoreActor = Cast<ASpawnableRing>(OtherActor))
	{
		for (TActorIterator<AUASCharacter> ActorItr(OtherActor->GetWorld()); ActorItr; ++ActorItr)
		{
			ActorItr->AddScore(ScoreActor->GetScore());
		}
		return true;
	}
	return false;
}

void UUASFireBehavior::OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, const FHitResult& Hit)
{
	UWorld* const World = OtherActor->GetWorld();

	TArray<FHitResult> HitResults;
	const ECollisionChannel ECC = ECollisionChannel::ECC_Visibility;

	FCollisionShape CollisionShape;
	CollisionShape.ShapeType = ECollisionShape::Sphere;
	CollisionShape.SetSphere(ExplodeHitRadius);
	FCollisionQueryParams Params;
	// Params.AddIgnoredActor(OtherActor);

	DrawDebugSphere(World, Hit.Location, ExplodeHitRadius, 32, FColor::Red, false, 2.0f);
	const bool bExplodeHit = World->SweepMultiByChannel(HitResults, Hit.Location, Hit.Location, FQuat::FQuat(), ECC, CollisionShape, Params);
	if (bExplodeHit)
	{
		OnExplode(Hit, HitResults);
	}

	if (OtherActor && OtherComp && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddRadialForce(Hit.Location, ExplodeHitRadius, ExplodeHitRadialStrength * ExplodeHitRadialStrength, ERadialImpulseFalloff::RIF_Linear);
	}

	if (CameraShake)
	{
		World->GetFirstPlayerController()->PlayerCameraManager->PlayCameraShake(CameraShake);
	}

	UGameplayStatics::SpawnEmitterAtLocation(World, HitParticle, Hit.ImpactPoint, FRotator::ZeroRotator, true, EPSCPoolMethod::AutoRelease);
	FActorHelper::SafePlaySound(World, HitSound, OtherActor->GetActorLocation());
}

void UUASFireBehavior::OnMissHit()
{
	FActorHelper::SafePlaySound(GetWorld(), FireSound, GetCaller()->GetActorLocation());
}

void UUASFireBehavior::OnExplode(const FHitResult& ExplodeHit, const TArray<FHitResult>& HitResults)
{
	for (FHitResult It : HitResults)
	{
		AActor* const HitActor = It.GetActor();
		if (!HitActor)
		{
			continue;
		}
		TryAddScoreFromActor(HitActor);
		if (USceneComponent* SceneComponent = HitActor->GetRootComponent())
		{
			if (UStaticMeshComponent* SM = Cast<UStaticMeshComponent>(SceneComponent))
			{
				if (SM->IsSimulatingPhysics())
				{
					SM->AddRadialImpulse(ExplodeHit.Location, ExplodeHitRadius, ExplodeHitRadialStrength, ERadialImpulseFalloff::RIF_Linear, true);
				}
			}
			else if (UDestructibleComponent* DM = Cast<UDestructibleComponent>(SceneComponent))
			{
				DM->ApplyRadiusDamage(TNumericLimits<float>::Max(), ExplodeHit.Location, ExplodeHitRadius, ExplodeHitRadialStrength, true);
				DM->AddRadialForce(ExplodeHit.Location, ExplodeHitRadius, ExplodeHitRadialStrength, ERadialImpulseFalloff::RIF_Linear);
			}
		}
	}
}
