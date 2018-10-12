// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "Lift.h"

ALift::ALift()
{
	PrimaryActorTick.bCanEverTick = false;
	NextLocation = FVector(0, 0, 550);
	Box = SetTrigger<UBoxComponent>("BoxTrigger");
}

void ALift::BeginTrigger(AActor* OtherActor)
{
	LiftActor(OtherActor);
}

void ALift::LiftActor(AActor* Actor)
{
	Actor->SetActorLocation(Actor->GetActorLocation() + NextLocation);
}

