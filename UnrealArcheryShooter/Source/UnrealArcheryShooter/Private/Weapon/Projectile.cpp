// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"
#include "Statics/ActorHelper.h"
#include "Components/SphereComponent.h"
#include "EngineUtils.h"
#include "CoreGame/UASCharacter.h"
#include "CoreGame/PlayerData.h"
#include "Spawners/SpawnableRing.h"
#include "ObjectPool/ActorPool.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Engine/Private/KismetTraceUtils.h"
#include "Particles/ParticleSystemComponent.h"

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;

	InitialLifeSpan = 0;
	InitialLifeSpanPooled = 3.0f;
	SphereRadius = 10;
	RadialStrength = 500;
	FireScoreCost = 20.0f;
}

void AProjectile::Disable()
{
	//Super::Disable(); // FIXME: temporary fix (no pooling)
	Destroy(); // FIXME: temporary fix (no pooling)
	//ProjectileMovement->Deactivate();
	//ProjectileMovement->UpdatedComponent = nullptr;
	//ProjectileMovement->bIsActive = 0;
	//UE_LOG(LogTemp, Warning, TEXT("Disabled"));
}

void AProjectile::Enable()
{
	//Super::Enable();
	//ProjectileMovement->Activate();
	FActorHelper::SafePlaySound(this, FireSound, GetActorLocation());
	//UE_LOG(LogTemp, Warning, TEXT("Enabled"));
}

void AProjectile::Fire()
{
	FHitResult OutHit;
	const FVector Start = GetActorLocation();
	FVector ForwardVector = GetActorForwardVector();
	FVector End = ((ForwardVector * RangeTrace) + Start);
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	DrawDebugLine(GetWorld(), Start, End, FColor::Green, true, 1.5f, 0, 2);
	const bool bTraceHit = GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility, CollisionParams);
	if (bTraceHit && OutHit.bBlockingHit)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("You are hitting: %s"), *OutHit.GetActor()->GetName()));
	}
	UParticleSystemComponent* ParticleComp = 
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BeamParticle, GetActorLocation(), GetActorRotation(), true, EPSCPoolMethod::AutoRelease);
	ParticleComp->SetBeamSourcePoint(0, Start, 0);
	ParticleComp->SetBeamTargetPoint(0, End, 0);
}

//void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, const FVector NormalImpulse, const FHitResult& Hit)
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
//
//bool AProjectile::TryAddScoreFromActor(AActor* OtherActor)
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
//
//void AProjectile::OnHitImpl(const bool bHitSomething, TArray<FHitResult> HitResults)
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
