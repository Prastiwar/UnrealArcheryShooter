// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "Engine.h"
#include "GameFramework/Actor.h"
#include "TriggerActor.generated.h"

UCLASS()
class UNREALARCHERYSHOOTER_API ATriggerActor : public AActor
{
	GENERATED_BODY()

public:
	ATriggerActor();

protected:
	template<class TReturnType>
	FORCEINLINE TReturnType* SetTrigger(FName TriggerName, bool bTransient = false)
	{
		TReturnType* Trigger = CreateDefaultSubobject<TReturnType>("TriggerName", bTransient);
		Trigger->OnComponentBeginOverlap.AddDynamic(this, &ATriggerActor::BeginOverlap);
		Trigger->OnComponentEndOverlap.AddDynamic(this, &ATriggerActor::EndOverlap);
		return Trigger;
	}

	virtual void BeginTrigger(AActor* OtherActor) {}
	virtual void EndTrigger(AActor* OtherActor) {}

	UFUNCTION()
		void BeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void EndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex);

};
