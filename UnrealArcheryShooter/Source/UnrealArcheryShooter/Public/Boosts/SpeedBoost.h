// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "Boost.h"
#include "SpeedBoost.generated.h"

UCLASS()
class UNREALARCHERYSHOOTER_API ASpeedBoost : public ABoost
{
	GENERATED_BODY()

public:
	ASpeedBoost();

protected:
	virtual void PickBoostImpl(AActor* AppliedActor) override;
	virtual void RevertBoostImpl(AActor* AppliedActor) override;

private:
	UPROPERTY(EditAnywhere)
		UBoxComponent* BoxTrigger;

};
