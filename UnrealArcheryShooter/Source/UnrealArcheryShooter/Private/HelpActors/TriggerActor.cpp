// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "TriggerActor.h"

ATriggerActor::ATriggerActor()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ATriggerActor::BeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		BeginTrigger(OtherActor);
	}
}

void ATriggerActor::EndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex)
{
	if (OtherActor && OtherActor != this)
	{
		EndTrigger(OtherActor);
	}
}
