// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "TriggerActor.h"
#include "Components/BoxComponent.h"
#include "Lift.generated.h"

UCLASS()
class UNREALARCHERYSHOOTER_API ALift : public ATriggerActor
{
	GENERATED_BODY()

public:
	ALift();

	UFUNCTION(BlueprintCallable)
		virtual void LiftActor(AActor* Actor);

protected:
	virtual void BeginTrigger(AActor* OtherActor) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UBoxComponent* Box;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector NextLocation;

};
