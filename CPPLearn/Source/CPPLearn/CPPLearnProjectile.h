// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPPLearnProjectile.generated.h"

UCLASS(config = Game)
class ACPPLearnProjectile : public AActor
{
	GENERATED_BODY()

		UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
		class USphereComponent* CollisionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
		class UProjectileMovementComponent* ProjectileMovement;

private:
	bool TryAddScoreFromActor(AActor* OtherActor);

protected:
	virtual void OnHitImpl();
	virtual void BeginPlay() override;

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
	ACPPLearnProjectile();

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	FORCEINLINE class USphereComponent* GetCollisionComp() const { return CollisionComp; }
	FORCEINLINE class UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }

	UFUNCTION(BlueprintCallable, Category = "Projectile")
		float GetFireCost();
};

