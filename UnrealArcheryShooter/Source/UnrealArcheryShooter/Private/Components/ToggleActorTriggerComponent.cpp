// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "ToggleActorTriggerComponent.h"
#include "Trigger.h"

UToggleActorTriggerComponent::UToggleActorTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bActiveOnEnter = true;
	bHiddenOnStart = true;
}

void UToggleActorTriggerComponent::SetTarget(AActor* const NewTarget)
{
	check(NewTarget);
	TargetActor = NewTarget;
	TargetActor->SetActorHiddenInGame(bHiddenOnStart);
	Toggle.SetToggle(!bHiddenOnStart);
}

void UToggleActorTriggerComponent::BeginPlay()
{
	Super::BeginPlay();

	if (!TargetActor)
	{
		SetTarget(GetOwner());
	}

	Trigger = Cast<ITrigger>(TriggerComponentRef.GetComponent(GetOwner()));
	if (Trigger)
	{
		Trigger->BindTrigger(this, &UToggleActorTriggerComponent::BeginTrigger, &UToggleActorTriggerComponent::EndTrigger);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UToggleActorTriggerComponent:: This component doesn't implement ITrigger interface"));
	}
}

void UToggleActorTriggerComponent::BeginTrigger(AActor* OtherActor, UPrimitiveComponent* OtherComp)
{
	TargetActor->SetActorHiddenInGame(!bActiveOnEnter);
	Toggle.SetToggle(bActiveOnEnter);
}

void UToggleActorTriggerComponent::EndTrigger(AActor* OtherActor, UPrimitiveComponent* OtherComp)
{
	TargetActor->SetActorHiddenInGame(bActiveOnEnter);
	Toggle.SetToggle(!bActiveOnEnter);
}
