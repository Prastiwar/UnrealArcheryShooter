// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "Boost.h"
#include "Togglers/ToggleActor.h"
#include "UASCharacter.h"

ABoost::ABoost()
{
	PrimaryActorTick.bCanEverTick = false;
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = StaticMesh;
}

void ABoost::SetTriggerComponent(UShapeComponent* Trigger)
{
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ABoost::BeginOverlap);
	Trigger->SetupAttachment(RootComponent);
}

void ABoost::BeginPlay()
{
	Super::BeginPlay();
}

void ABoost::BeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Boost.AppliedActor = OtherActor;
	PickBoostImpl(OtherActor);
	GetWorld()->GetTimerManager().SetTimer(Boost.TimerHandle, this, &ABoost::StopBoost, 1.0f, false, Boost.TimeLast);
	AToggleActor::SetActive(this, false);
}

void ABoost::StopBoost()
{
	GetWorld()->GetTimerManager().ClearTimer(Boost.TimerHandle);
	RevertBoostImpl(Boost.AppliedActor);
	Destroy();
}
