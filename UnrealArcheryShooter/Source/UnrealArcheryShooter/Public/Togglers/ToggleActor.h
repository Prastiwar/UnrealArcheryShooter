// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "Engine.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "ToggleActor.generated.h"

UCLASS()
class UNREALARCHERYSHOOTER_API AToggleActor : public AActor
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

	UPROPERTY(EditAnywhere)
		bool bActiveOnOverlap;

	UPROPERTY(EditAnywhere)
		UBoxComponent* TriggerBox;

	UFUNCTION()
		void BeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void EndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex);
};
