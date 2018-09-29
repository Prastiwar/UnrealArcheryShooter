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

	/** If false, actor is hidden in game with disabled tick and collision*/
	static void SetActive(AActor* Actor, bool Active)
	{
		Actor->SetActorHiddenInGame(!Active);
		Actor->SetActorEnableCollision(Active);
		Actor->SetActorTickEnabled(Active);
	}

protected:
	virtual void BeginPlay() override;
	virtual void Activated(bool bActive, AActor* OverlappedActor) {}
	virtual void BeginTrigger(AActor* OtherActor);
	virtual void EndTrigger(AActor* OtherActor);

	UPROPERTY(EditAnywhere)
		bool bActiveOnOverlap;

	UPROPERTY(EditAnywhere)
		UBoxComponent* TriggerBox;
};
