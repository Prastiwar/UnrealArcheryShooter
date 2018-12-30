// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "GameFramework/Actor.h"
#include "BoostData.h"
#include "Spawnable.h"
#include "Boost.generated.h"

UCLASS()
class UNREALARCHERYSHOOTER_API ABoost : public AActor, public ISpawnable
{
	GENERATED_BODY()

public:
	ABoost();

protected:
	virtual void PickBoostImpl(AActor* AppliedActor) {}
	virtual void RevertBoostImpl(AActor* AppliedActor) {}

	// ISpawnable interface
	virtual bool CanBeSpawned() const override;
	virtual UClass* GetSpawnableClass() const override { return this->GetClass(); }
	/////////////////////////

	void SetTriggerComponent(class UShapeComponent* Trigger);

	UPROPERTY(EditAnywhere, Category = "Boost")
		FBoostData Boost;

	UPROPERTY(VisibleAnywhere, Category = "Boost")
		UStaticMeshComponent* StaticMesh;

private:
	UFUNCTION(BlueprintCallable)
		void StopBoost();

	UFUNCTION()
		void BeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, const int32 OtherBodyIndex, const bool bFromSweep, const FHitResult& SweepResult);

};
