// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "FireBehavior.generated.h"

UCLASS(BlueprintType, Blueprintable)
class UNREALARCHERYSHOOTER_API UFireBehavior : public UObject
{
	GENERATED_BODY()

public:
	UFireBehavior();

	UFUNCTION(BlueprintCallable)
		FORCEINLINE float GetFireCost() const { return FireCost; }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE UAnimMontage* GetFireAnimation() const { return FireAnimation; }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE AActor* GetCaller() const { return CallerPrivate; }

	virtual class UWorld* GetWorld() const override { return WorldPrivate; }

	void Fire(AActor* Outer, const FVector Start, const FVector Forward);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		USoundBase* FireSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		USoundBase* HitSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UParticleSystem* HitParticle;

	UPROPERTY(EditAnywhere)
		UParticleSystem* BeamParticle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TSubclassOf<UCameraShake> CameraShake;

	UPROPERTY(EditAnywhere)
		TEnumAsByte<ETraceTypeQuery> TraceType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class UAnimMontage* FireAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float FireCost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ExplodeHitRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ExplodeHitRadialStrength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float FireRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ParticleLifetime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector PrecisionOffset;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void OnFire(const FVector Start, const FVector Forward);

	virtual void OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, const FHitResult& Hit) {}

	virtual void OnMissHit() {}

private:
	UWorld* WorldPrivate;
	AActor* CallerPrivate;

};
