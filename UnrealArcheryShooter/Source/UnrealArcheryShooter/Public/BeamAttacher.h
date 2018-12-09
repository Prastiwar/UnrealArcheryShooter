// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "Toggle.h"
#include "GameFramework/Actor.h"
#include "BeamAttacher.generated.h"

UCLASS()
class UNREALARCHERYSHOOTER_API ABeamAttacher : public AActor
{
	GENERATED_BODY()

public:
	ABeamAttacher();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector AttachOffset;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UParticleSystemComponent* BeamParticle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class UShapeComponent* TriggerShape;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> TargetClass;

	FToggle Toggle;
	AActor* AttachTarget;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	virtual void Toggled(const bool bActive);
	void TriggerToggle(AActor* OtherActor, UPrimitiveComponent* OtherComp);

	virtual void AttachBeamToTarget(AActor* Target);

};
