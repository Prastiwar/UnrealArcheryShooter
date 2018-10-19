// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "TriggerActor.h"
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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UBoxComponent* TriggerBox;

	virtual void BeginPlay() override;
	virtual void BeginTrigger(AActor* OtherActor);
	virtual void EndTrigger(AActor* OtherActor);
	virtual void Activated(const bool bActive, AActor* OverlappedActor) {}
};
