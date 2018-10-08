// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "AttributeComponent.h"

UAttributeComponent::UAttributeComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UAttributeComponent::BeginPlay()
{
	Super::BeginPlay();
	for (TSubclassOf<class UTPAttribute> Attribute : AttributeClasses)
	{
		Attributes.Add(Attribute->GetDefaultObject<UTPAttribute>());
	}
}
