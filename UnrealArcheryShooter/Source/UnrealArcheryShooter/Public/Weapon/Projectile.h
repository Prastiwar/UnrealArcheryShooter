// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "ObjectPool/PoolableActor.h"
#include "ObjectPool/ActorPool.h"
#include "Projectile.generated.h"

UCLASS(config = Game)
class UNREALARCHERYSHOOTER_API AProjectile : public APoolableActor
{
	GENERATED_BODY()

public:
	AProjectile();

	UFUNCTION(BlueprintCallable)
		FORCEINLINE float GetFireCost() const { return FireScoreCost; }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE float GetSphereRadius() const { return SphereRadius; }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE float GetRadialStrength() const { return RadialStrength; }

	virtual void Fire();
	virtual void Disable() override;
	virtual void Enable() override;

protected:
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

	UPROPERTY(EditAnywhere)
		TEnumAsByte<ETraceTypeQuery> TraceType;

	UPROPERTY(EditAnywhere)
		float RangeTrace;

	UPROPERTY(EditAnywhere)
		UParticleSystem* BeamParticle;

private:
	//bool TryAddScoreFromActor(AActor* OtherActor);

};
