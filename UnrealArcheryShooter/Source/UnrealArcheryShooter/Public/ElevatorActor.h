// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "Engine/StaticMeshActor.h"
#include "ElevatorActor.generated.h"

UCLASS()
class UNREALARCHERYSHOOTER_API AElevatorActor : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	AElevatorActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ActivateLiftDelay;

	UFUNCTION(BlueprintCallable)
		FORCEINLINE UFloatingActorComponent* GetFloatingComponent() { return FloatingComp; }

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnTrigger(AActor* OtherActor, UPrimitiveComponent* OtherComp);

	UFUNCTION()
		void OnFloatingDirectionChanged(const bool bIsReversed);

private:
	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* LeverMesh;

	UPROPERTY(VisibleAnywhere)
		class UFloatingActorComponent* FloatingComp;

	UPROPERTY(VisibleAnywhere)
		class UShapeComponent* TriggerShape;

};
