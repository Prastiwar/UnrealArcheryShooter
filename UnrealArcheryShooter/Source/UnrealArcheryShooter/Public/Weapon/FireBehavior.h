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

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void Fire(const UWorld* World, const FVector Start, const FVector Forward);

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

	UPROPERTY(EditAnywhere)
		float FireRange;

	virtual void Fire_Implementation(const UWorld* World, const FVector Start, const FVector Forward);

	virtual void OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, const FHitResult& Hit) {}

};
