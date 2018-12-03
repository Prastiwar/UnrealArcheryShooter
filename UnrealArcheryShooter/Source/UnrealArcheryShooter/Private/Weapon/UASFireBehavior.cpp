// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "UASFireBehavior.h"
#include "EngineUtils.h"

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
	TArray<FHitResult> HitResults;
	const FVector StartLocation = OtherActor->GetActorLocation();
	const FVector EndLocation = OtherActor->GetActorLocation();
	const ECollisionChannel ECC = ECollisionChannel::ECC_Visibility;
	FCollisionShape CollisionShape;
	CollisionShape.ShapeType = ECollisionShape::Sphere;
	CollisionShape.SetSphere(ExplodeHitRadius);
	UWorld* const World = OtherActor->GetWorld();
	const bool bHitSomething = World->SweepMultiByChannel(HitResults, StartLocation, EndLocation, FQuat::FQuat(), ECC, CollisionShape);

	if (OtherActor && OtherComp && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(Hit.Normal * ExplodeHitRadius, OtherActor->GetActorLocation());
	}
	if (bHitSomething)
	{
		if (CameraShake)
		{
			World->GetFirstPlayerController()->PlayerCameraManager->PlayCameraShake(CameraShake);
		}
		OnExplode(HitResults);
	}
	UGameplayStatics::SpawnEmitterAtLocation(World, HitParticle, Hit.ImpactPoint, FRotator::ZeroRotator, true, EPSCPoolMethod::AutoRelease);
	FActorHelper::SafePlaySound(World, HitSound, OtherActor->GetActorLocation());
}

void UUASFireBehavior::OnMissHit()
{
	FActorHelper::SafePlaySound(GetWorld(), HitSound, GetCaller()->GetActorLocation());
}

void UUASFireBehavior::OnExplode(TArray<FHitResult> HitResults)
{
	for (auto It = HitResults.CreateIterator(); It; It++)
	{
		AActor* const HitActor = It->GetActor();
		if (!HitActor)
		{
			continue;
		}
		TryAddScoreFromActor(HitActor);
		if (USceneComponent* SceneComponent = HitActor->GetRootComponent())
		{
			if (UStaticMeshComponent* SM = Cast<UStaticMeshComponent>(SceneComponent))
			{
				SM->AddRadialImpulse(HitActor->GetActorLocation(), ExplodeHitRadius, ExplodeHitRadialStrength, ERadialImpulseFalloff::RIF_Linear, true);
			}
			else if (UDestructibleComponent* DM = Cast<UDestructibleComponent>(SceneComponent))
			{
				DM->ApplyRadiusDamage(1000, HitActor->GetActorLocation(), ExplodeHitRadius, ExplodeHitRadialStrength, true);
				DM->AddRadialImpulse(HitActor->GetActorLocation(), ExplodeHitRadius, ExplodeHitRadialStrength, ERadialImpulseFalloff::RIF_Linear, true);
			}
		}
	}
}
