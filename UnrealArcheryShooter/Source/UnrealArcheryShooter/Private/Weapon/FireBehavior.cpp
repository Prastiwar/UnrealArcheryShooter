// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "FireBehavior.h"

UFireBehavior::UFireBehavior()
{
	ExplodeHitRadius = 10.0f;
	ExplodeHitRadialStrength = 500.0f;
	FireCost = 20.0f;
	FireRange = 10000.0f;
}

void UFireBehavior::Fire(const UWorld* World, const FVector Start, const FVector Forward)
{
	FHitResult OutHit;
	FVector End = ((Forward * FireRange) + Start);
	FCollisionQueryParams CollisionParams;

	const bool bTraceHit = World->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility, CollisionParams);
	if (bTraceHit && OutHit.bBlockingHit)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("You are hitting: %s"), *OutHit.GetActor()->GetName()));
	}

	UParticleSystemComponent* ParticleComp =
		UGameplayStatics::SpawnEmitterAtLocation(World, BeamParticle, Start, FRotator::ZeroRotator, FVector(1.f), true, EPSCPoolMethod::AutoRelease);
	ParticleComp->SetBeamSourcePoint(0, Start, 0);
	ParticleComp->SetBeamTargetPoint(0, End, 0);
}

//void UFireBehavior::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, const FVector NormalImpulse, const FHitResult& Hit)
//{
//	TArray<FHitResult> HitResults;
//	const FVector StartLocation = GetActorLocation();
//	const FVector EndLocation = GetActorLocation();
//	const ECollisionChannel ECC = ECollisionChannel::ECC_Visibility;
//	FCollisionShape CollisionShape;
//	CollisionShape.ShapeType = ECollisionShape::Sphere;
//	CollisionShape.SetSphere(SphereRadius);
//	const bool bHitSomething = GetWorld()->SweepMultiByChannel(HitResults, StartLocation, EndLocation, FQuat::FQuat(), ECC, CollisionShape);
//
//	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL) && OtherComp->IsSimulatingPhysics())
//	{
//		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
//	}
//	OnHitImpl(bHitSomething, HitResults);
//}

//bool UFireBehavior::TryAddScoreFromActor(AActor* OtherActor)
//{
//	if (ASpawnableRing* const ScoreActor = Cast<ASpawnableRing>(OtherActor))
//	{
//		for (TActorIterator<AUASCharacter> ActorItr(GetWorld()); ActorItr; ++ActorItr)
//		{
//			ActorItr->AddScore(ScoreActor->GetScore());
//		}
//		return true;
//	}
//	return false;
//}

//void UFireBehavior::OnHitImpl(const bool bHitSomething, TArray<FHitResult> HitResults)
//{
//	if (bHitSomething)
//	{
//		if (CameraShake)
//		{
//			GetWorld()->GetFirstPlayerController()->PlayerCameraManager->PlayCameraShake(CameraShake);
//		}
//		for (auto It = HitResults.CreateIterator(); It; It++)
//		{
//			AActor* const HitActor = It->GetActor();
//			if (!HitActor || HitActor == this)
//			{
//				continue;
//			}
//			TryAddScoreFromActor(HitActor);
//			if (USceneComponent* SceneComponent = HitActor->GetRootComponent())
//			{
//				if (UStaticMeshComponent* SM = Cast<UStaticMeshComponent>(SceneComponent))
//				{
//					SM->AddRadialImpulse(GetActorLocation(), SphereRadius, RadialStrength, ERadialImpulseFalloff::RIF_Linear, true);
//				}
//				else if (UDestructibleComponent* DM = Cast<UDestructibleComponent>(SceneComponent))
//				{
//					DM->ApplyRadiusDamage(1000, GetActorLocation(), SphereRadius, RadialStrength, true);
//					DM->AddRadialImpulse(GetActorLocation(), SphereRadius, RadialStrength, ERadialImpulseFalloff::RIF_Linear, true);
//				}
//			}
//		}
//	}
//	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticle, GetActorLocation(), GetActorRotation(), true, EPSCPoolMethod::AutoRelease);
//	FActorHelper::SafePlaySound(this, HitSound, GetActorLocation());
//	// FIXME: temporary fix (no pooling)
//	//if (!ReturnToSelfPool())
//	//{
//		//UE_LOG(LogTemp, Warning, TEXT("No Pool"));
//		Destroy();
//	//}
//}