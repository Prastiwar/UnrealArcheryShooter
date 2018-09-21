// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "Lift.h"

ALift::ALift()
{
	PrimaryActorTick.bCanEverTick = false;
	NextLocation = FVector(0, 0, 550);

	Box = CreateDefaultSubobject<UBoxComponent>("BoxTrigger");
	Box->OnComponentBeginOverlap.AddDynamic(this, &ALift::BeginOverlap);
}

void ALift::BeginPlay()
{
	Super::BeginPlay();
}

void ALift::BeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
	{
		OtherActor->SetActorLocation(OtherActor->GetActorLocation() + NextLocation, bFromSweep);
	}
}

