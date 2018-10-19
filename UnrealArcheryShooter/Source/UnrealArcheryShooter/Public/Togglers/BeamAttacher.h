// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "Togglers/ToggleActor.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
#include "BeamAttacher.generated.h"

UCLASS()
class UNREALARCHERYSHOOTER_API ABeamAttacher : public AToggleActor
{
	GENERATED_BODY()

public:
	ABeamAttacher();

	UFUNCTION(BlueprintCallable)
		FORCEINLINE FVector GetAttachOffset() const { return AttachOffset; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UParticleSystemComponent* BeamParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector AttachOffset;

	class AUASCharacter* Player;
	FTimerHandle TimerHandle;
	float UpdateRate;

	virtual void BeginPlay() override;
	virtual void Activated(const bool bActive, AActor* OverlappedActor) override;
	virtual void AttachBeam();

};
