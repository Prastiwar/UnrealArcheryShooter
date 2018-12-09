// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "Trigger.h"
#include "Components/SphereComponent.h"
#include "TriggerSphereComponent.generated.h"

/**
 * USphereComponent with automatically setup simplified overlap (trigger) functions
 */
UCLASS(ClassGroup = (Trigger), meta = (BlueprintSpawnableComponent))
class UNREALARCHERYSHOOTER_API UTriggerSphereComponent : public USphereComponent, public ITrigger
{
	GENERATED_BODY()

public:
	UTriggerSphereComponent()
	{
		OnComponentBeginOverlap.AddDynamic(this, &UTriggerSphereComponent::BeginOverlap);
		OnComponentEndOverlap.AddDynamic(this, &UTriggerSphereComponent::EndOverlap);
	}
	
};
