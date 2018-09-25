// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "Engine.h"
#include "GameFramework/Actor.h"
#include "BoostData.h"
#include "Boost.generated.h"

UCLASS()
class UNREALARCHERYSHOOTER_API ABoost : public AActor
{
	GENERATED_BODY()

public:
	ABoost();

protected:
	virtual void BeginPlay() override;
	virtual void PickBoostImpl(AActor* AppliedActor) { }
	virtual void RevertBoostImpl(AActor* AppliedActor) { }

	void SetTriggerComponent(UShapeComponent* Trigger);

	/** If false, actor is hidden in game with disabled tick and collision*/
	void SetActive(bool Active);

	UPROPERTY(EditAnywhere, Category = "Boost")
		FBoostData Boost;

	UPROPERTY(EditAnywhere, Category = "Boost")
		UStaticMeshComponent* StaticMesh;

private:
	void StopBoost();

	UFUNCTION(BlueprintCallable)
		void BeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
