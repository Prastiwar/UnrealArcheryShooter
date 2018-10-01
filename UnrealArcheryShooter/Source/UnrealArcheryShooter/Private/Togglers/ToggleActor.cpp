// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "ToggleActor.h"

AToggleActor::AToggleActor()
{
	PrimaryActorTick.bCanEverTick = false;
	TriggerBox = SetTrigger<UBoxComponent>("TriggerBox");
	TriggerBox->InitBoxExtent(FVector(50, 50, 50));
	RootComponent = TriggerBox;
}

void AToggleActor::BeginPlay()
{
	Super::BeginPlay();
	this->SetActorHiddenInGame(bActiveOnOverlap);
}

void AToggleActor::BeginTrigger(AActor* OtherActor)
{
	this->SetActorHiddenInGame(!bActiveOnOverlap);
	Activated(bActiveOnOverlap, OtherActor);
}

void AToggleActor::EndTrigger(AActor* OtherActor)
{
	this->SetActorHiddenInGame(bActiveOnOverlap);
	Activated(!bActiveOnOverlap, OtherActor);
}
