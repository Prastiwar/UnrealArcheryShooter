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

AProjectile::AProjectile()
{
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->SetSimulatePhysics(true);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	RootComponent = CollisionComp;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	StaticMesh->SetupAttachment(RootComponent);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	InitialLifeSpan = 3.0f;
	SphereRadius = 10;
	RadialStrength = 500;
	FireScoreCost = 20.0f;
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	FActorHelper::SafePlaySound(this, FireSound, GetActorLocation());
}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, const FVector NormalImpulse, const FHitResult& Hit)
{
	TArray<FHitResult> HitResults;
	const FVector StartLocation = GetActorLocation();
	const FVector EndLocation = GetActorLocation();
	const ECollisionChannel ECC = ECollisionChannel::ECC_Visibility;
	FCollisionShape CollisionShape;
	CollisionShape.ShapeType = ECollisionShape::Sphere;
	CollisionShape.SetSphere(SphereRadius);
	const bool bHitSomething = GetWorld()->SweepMultiByChannel(HitResults, StartLocation, EndLocation, FQuat::FQuat(), ECC, CollisionShape);

	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
	}
	OnHitImpl(bHitSomething, HitResults);
}

bool AProjectile::TryAddScoreFromActor(AActor* OtherActor)
{
	if (ASpawnableRing* const ScoreActor = Cast<ASpawnableRing>(OtherActor))
	{
		for (TActorIterator<AUASCharacter> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		{
			ActorItr->AddScore(ScoreActor->GetScore());
		}
		return true;
	}
	return false;
}

void AProjectile::OnHitImpl(const bool bHitSomething, TArray<FHitResult> HitResults)
{
	if (bHitSomething)
	{
		if (CameraShake)
		{
			GetWorld()->GetFirstPlayerController()->PlayerCameraManager->PlayCameraShake(CameraShake);
		}
		for (auto It = HitResults.CreateIterator(); It; It++)
		{
			AActor* const HitActor = It->GetActor();
			if (!HitActor || HitActor == this)
			{
				continue;
			}
			TryAddScoreFromActor(HitActor);
			if (USceneComponent* SceneComponent = HitActor->GetRootComponent())
			{
				if (UStaticMeshComponent* SM = Cast<UStaticMeshComponent>(SceneComponent))
				{
					SM->AddRadialImpulse(GetActorLocation(), SphereRadius, RadialStrength, ERadialImpulseFalloff::RIF_Linear, true);
				}
				else if (UDestructibleComponent* DM = Cast<UDestructibleComponent>(SceneComponent))
				{
					DM->ApplyRadiusDamage(1000, GetActorLocation(), SphereRadius, RadialStrength, true);
					DM->AddRadialImpulse(GetActorLocation(), SphereRadius, RadialStrength, ERadialImpulseFalloff::RIF_Linear, true);
				}
			}
		}
	}
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticle, GetActorLocation());
	FActorHelper::SafePlaySound(this, HitSound, GetActorLocation());
	Destroy();
}