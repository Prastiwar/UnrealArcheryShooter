// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "Togglers/ToggleActor.h"
#include "BeamAttacher.generated.h"

UCLASS()
class UNREALARCHERYSHOOTER_API ABeamAttacher : public AToggleActor
{
	GENERATED_BODY()
	
public:	
	ABeamAttacher();

protected:
	virtual void Activated(bool bActive, AActor* OverlappedActor) override;
	virtual void AttachBeam();
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;

	FTimerHandle TimerHandle;
	float UpdateRate; 
	AActor* AttachedActor;
	
	UPROPERTY(EditAnywhere)
		UParticleSystemComponent* BeamParticle;
	
	UPROPERTY(EditAnywhere)
		FVector AttachOffset;

};
