// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS(config = Game)
class UNREALARCHERYSHOOTER_API AProjectile : public AActor
{
	GENERATED_BODY()

public:
	AProjectile();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
		class USphereComponent* CollisionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
		class UProjectileMovementComponent* ProjectileMovement;

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, const FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION(BlueprintCallable)
		FORCEINLINE float GetFireCost() const { return FireScoreCost; }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE float GetSphereRadius() const { return SphereRadius; }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE float GetRadialStrength() const { return RadialStrength; }

protected:
	virtual void OnHitImpl(const bool bHitSomething, TArray<FHitResult> HitResults);
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		USoundBase* FireSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		USoundBase* HitSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UParticleSystem* HitParticle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TSubclassOf<UCameraShake> CameraShake;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float FireScoreCost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float SphereRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float RadialStrength;

private:
	bool TryAddScoreFromActor(AActor* OtherActor);

};