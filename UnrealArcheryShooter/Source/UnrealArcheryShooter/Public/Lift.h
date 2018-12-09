// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "GameFramework/Actor.h"
#include "Lift.generated.h"

UCLASS()
class UNREALARCHERYSHOOTER_API ALift : public AActor
{
	GENERATED_BODY()

public:
	ALift();

	UFUNCTION(BlueprintCallable)
		virtual void LiftActor(AActor* Actor);

protected:
	void BeginTrigger(AActor* OtherActor, UPrimitiveComponent* OtherComp);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class UShapeComponent* TriggerShape;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector NextLocation;

};
