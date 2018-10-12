// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "TriggerActor.h"
#include "Components/BoxComponent.h"
#include "ToggleActor.generated.h"

UCLASS()
class UNREALARCHERYSHOOTER_API AToggleActor : public ATriggerActor
{
	GENERATED_BODY()
	
public:	
	AToggleActor();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bActiveOnOverlap;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UBoxComponent* TriggerBox;

	virtual void BeginPlay() override;
	virtual void BeginTrigger(AActor* OtherActor);
	virtual void EndTrigger(AActor* OtherActor);
	virtual void Activated(bool bActive, AActor* OverlappedActor) {}
};
