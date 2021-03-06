// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "Boost.h"
#include "Components/ShapeComponent.h"
#include "Static/ActorHelper.h"

ABoost::ABoost()
{
	PrimaryActorTick.bCanEverTick = false;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = StaticMesh;
}

bool ABoost::CanBeSpawned() const
{
	FHitResult Hit;
	TArray<FHitResult> HitResults;
	const FVector Location = GetActorLocation();
	const ECollisionChannel ECC = ECollisionChannel::ECC_WorldStatic;
	FCollisionShape CollisionShape;
	CollisionShape.ShapeType = ECollisionShape::Box;
	CollisionShape.SetBox(GetActorScale());
	const bool bHitSomething = GetWorld()->SweepMultiByChannel(HitResults, Location, Location, FQuat::FQuat(), ECC, CollisionShape);
	return !bHitSomething && ISpawnable::CanBeSpawned();
}

void ABoost::SetTriggerComponent(UShapeComponent* Trigger)
{
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ABoost::BeginOverlap);
	Trigger->SetupAttachment(RootComponent);
}

void ABoost::BeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, const int32 OtherBodyIndex, const bool bFromSweep, const FHitResult& SweepResult)
{
	Boost.AppliedActor = OtherActor;
	PickBoostImpl(OtherActor);
	GetWorld()->GetTimerManager().SetTimer(Boost.TimerHandle, this, &ABoost::StopBoost, 1.0f, false, Boost.TimeLast);
	FActorHelper::SetActive(this, false);
}

void ABoost::StopBoost()
{
	GetWorld()->GetTimerManager().ClearTimer(Boost.TimerHandle);
	RevertBoostImpl(Boost.AppliedActor);
	Destroy();
}
