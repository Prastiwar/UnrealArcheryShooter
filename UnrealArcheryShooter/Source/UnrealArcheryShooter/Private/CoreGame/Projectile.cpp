// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "EngineUtils.h"
#include "UASCharacter.h"
#include "Spawners/SpawnableRing.h"
#include "Data/PlayerData.h"

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
	if (FireSound != NULL)
	{
		UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
	}
}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
	}
	OnHitImpl();
}

bool AProjectile::TryAddScoreFromActor(AActor* OtherActor)
{
	if (ASpawnableRing* ScoreActor = Cast<ASpawnableRing>(OtherActor))
	{
		for (TActorIterator<AUASCharacter> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		{
			ActorItr->AddScore(ScoreActor->GetScore());
		}
		if (UDestructibleComponent* DM = Cast<UDestructibleComponent>(ScoreActor->GetRootComponent()))
		{
			DM->AddRadialImpulse(GetActorLocation(), SphereRadius, RadialStrength, ERadialImpulseFalloff::RIF_Linear, true);
			DM->ApplyRadiusDamage(1000, GetActorLocation(), SphereRadius, RadialStrength, true);
		}
		return true;
	}
	return false;
}

void AProjectile::OnHitImpl()
{
	TArray<FHitResult> HitResults;
	FVector StartLocation = GetActorLocation();
	FVector EndLocation = GetActorLocation();
	ECollisionChannel ECC = ECollisionChannel::ECC_Visibility;
	FCollisionShape CollisionShape;
	CollisionShape.ShapeType = ECollisionShape::Sphere;
	CollisionShape.SetSphere(SphereRadius);

	bool bHitSomething = GetWorld()->SweepMultiByChannel(HitResults, StartLocation, EndLocation, FQuat::FQuat(), ECC, CollisionShape);
	if (bHitSomething)
	{
		if (CameraShake)
		{
			GetWorld()->GetFirstPlayerController()->PlayerCameraManager->PlayCameraShake(CameraShake);
		}

		for (auto It = HitResults.CreateIterator(); It; It++)
		{
			if (!TryAddScoreFromActor(It->GetActor()))
			{
				if (AActor* HitActor = It->GetActor())
				{
					if (USceneComponent* SceneComponent = It->GetActor()->GetRootComponent())
					{
						if (UStaticMeshComponent* SM = Cast<UStaticMeshComponent>(SceneComponent))
						{
							SM->AddRadialImpulse(GetActorLocation(), SphereRadius, RadialStrength, ERadialImpulseFalloff::RIF_Linear, true);
						}
						else if (UDestructibleComponent* DM = Cast<UDestructibleComponent>(It->GetActor()->GetRootComponent()))
						{
							DM->ApplyRadiusDamage(1000, GetActorLocation(), SphereRadius, RadialStrength, true);
						}
					}
				}
			}
		}
	}
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticle, GetActorLocation());

	if (HitSound != NULL)
	{
		UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
	}
	Destroy();
}
