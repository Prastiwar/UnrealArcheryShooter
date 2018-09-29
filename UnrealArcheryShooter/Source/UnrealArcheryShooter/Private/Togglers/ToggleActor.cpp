// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "ToggleActor.h"

AToggleActor::AToggleActor()
{
	PrimaryActorTick.bCanEverTick = false;
	TriggerBox = CreateDefaultSubobject<UBoxComponent>("TriggerBox");
	TriggerBox->InitBoxExtent(FVector(50, 50, 50));
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AToggleActor::BeginOverlap);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &AToggleActor::EndOverlap);
	RootComponent = TriggerBox;
}

void AToggleActor::BeginPlay()
{
	Super::BeginPlay();
	this->SetActorHiddenInGame(bActiveOnOverlap);
}

void AToggleActor::BeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
	{
		this->SetActorHiddenInGame(!bActiveOnOverlap);
		Activated(bActiveOnOverlap, OtherActor);
	}
}

void AToggleActor::EndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex)
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
	{
		this->SetActorHiddenInGame(bActiveOnOverlap);
		Activated(bActiveOnOverlap, OtherActor);
	}
}
