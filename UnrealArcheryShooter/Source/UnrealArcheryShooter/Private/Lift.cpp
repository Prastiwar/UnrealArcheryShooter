// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "Lift.h"
#include "TriggerBoxComponent.h"

ALift::ALift()
{
	PrimaryActorTick.bCanEverTick = false;
	NextLocation = FVector(0, 0, 550);

	// TODO: Changeable shape
	TriggerShape = Cast<UShapeComponent>(CreateDefaultSubobject<UTriggerBoxComponent>(TEXT("TriggerShape")));
	RootComponent = TriggerShape;
	if (ITrigger* Trigger = Cast<ITrigger>(TriggerShape))
	{
		Trigger->BindTrigger(this, &ALift::BeginTrigger, nullptr);
	}
}

void ALift::BeginTrigger(AActor* OtherActor, UPrimitiveComponent* OtherComp)
{
	LiftActor(OtherActor);
}

void ALift::LiftActor(AActor* Actor)
{
	Actor->SetActorLocation(Actor->GetActorLocation() + NextLocation);
}

