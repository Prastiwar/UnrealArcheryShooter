// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "TriggerActor.h"
#include "Lift.generated.h"

UCLASS()
class UNREALARCHERYSHOOTER_API ALift : public ATriggerActor
{
	GENERATED_BODY()

public:
	ALift();

protected:
	virtual void BeginPlay() override;

private:
	virtual void BeginTrigger(AActor* OtherActor) override;

	UPROPERTY(EditAnywhere)
		UBoxComponent* Box;

	UPROPERTY(EditAnywhere)
		FVector NextLocation;

};
