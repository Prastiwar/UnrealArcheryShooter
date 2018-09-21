// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS(config = Game)
class UNREALARCHERYSHOOTER_API AProjectile : public AActor
{
	GENERATED_BODY()

private:
	bool TryAddScoreFromActor(AActor* OtherActor);

protected:
	virtual void OnHitImpl();
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "FPPProjectile")
		UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, Category = "FPPProjectile")
		USoundBase* FireSound;

	UPROPERTY(EditAnywhere, Category = "FPPProjectile")
		USoundBase* HitSound;

	UPROPERTY(EditAnywhere, Category = "FPPProjectile")
		UParticleSystem* HitParticle;

	UPROPERTY(EditAnywhere, Category = "FPPProjectile")
		float HitForce;

	UPROPERTY(EditAnywhere, Category = "FPPProjectile")
		float FireScoreCost;

	UPROPERTY(EditAnywhere, Category = "FPPProjectile")
		float SphereRadius;

	UPROPERTY(EditAnywhere, Category = "FPPProjectile")
		float RadialStrength;

public:
	AProjectile();

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	FORCEINLINE class USphereComponent* GetCollisionComp() const { return CollisionComp; }
	FORCEINLINE class UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }
	
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
		class USphereComponent* CollisionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
		class UProjectileMovementComponent* ProjectileMovement;

	UFUNCTION(BlueprintCallable, Category = "Projectile")
		float GetFireCost();

};
