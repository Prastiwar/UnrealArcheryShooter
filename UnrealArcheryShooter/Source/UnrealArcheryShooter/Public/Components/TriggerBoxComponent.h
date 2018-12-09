// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "Trigger.h"
#include "Components/BoxComponent.h"
#include "TriggerBoxComponent.generated.h"

/**
 * UBoxComponent with automatically setup simplified overlap (trigger) functions
 */
UCLASS(ClassGroup = (Trigger), meta = (BlueprintSpawnableComponent))
class UNREALARCHERYSHOOTER_API UTriggerBoxComponent : public UBoxComponent, public ITrigger
{
	GENERATED_BODY()

public:
	UTriggerBoxComponent()
	{
		OnComponentBeginOverlap.AddDynamic(this, &UTriggerBoxComponent::BeginOverlap);
		OnComponentEndOverlap.AddDynamic(this, &UTriggerBoxComponent::EndOverlap);
	}

};
