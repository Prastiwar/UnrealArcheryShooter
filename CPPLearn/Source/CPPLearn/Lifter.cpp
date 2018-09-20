// // Copyright 2018-2019 Tomasz Piowczyk, MIT License

#include "Lifter.h"
#include "Engine.h"

ALifter::ALifter()
{
	PrimaryActorTick.bCanEverTick = false;
	NextLocation = FVector(0, 0, 550);

	Box = CreateDefaultSubobject<UBoxComponent>("BoxTrigger");
	Box->OnComponentBeginOverlap.AddDynamic(this, &ALifter::BeginOverlap);
}

void ALifter::BeginPlay()
{
	Super::BeginPlay();
}

void ALifter::BeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
	{
		OtherActor->SetActorLocation(OtherActor->GetActorLocation() + NextLocation, bFromSweep);
	}
}
