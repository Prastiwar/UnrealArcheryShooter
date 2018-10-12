// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "Togglers/ToggleActor.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
#include "CoreGame/UASCharacter.h"
#include "BeamAttacher.generated.h"

UCLASS()
class UNREALARCHERYSHOOTER_API ABeamAttacher : public AToggleActor
{
	GENERATED_BODY()

public:
	ABeamAttacher();

	UFUNCTION(BlueprintCallable)
		FORCEINLINE FVector GetAttachOffset() { return AttachOffset; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UParticleSystemComponent* BeamParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector AttachOffset;

	AUASCharacter* Player;
	FTimerHandle TimerHandle;
	float UpdateRate;

	virtual void BeginPlay() override;
	virtual void Activated(bool bActive, AActor* OverlappedActor) override;
	virtual void AttachBeam();

};
