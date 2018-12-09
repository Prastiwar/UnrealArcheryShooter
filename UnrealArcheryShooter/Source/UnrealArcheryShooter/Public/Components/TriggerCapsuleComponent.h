// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "Trigger.h"
#include "Components/CapsuleComponent.h"
#include "TriggerCapsuleComponent.generated.h"

/**
 * UCapsuleComponent with automatically setup simplified overlap (trigger) functions
 */
UCLASS(ClassGroup = (Trigger), meta = (BlueprintSpawnableComponent))
class UNREALARCHERYSHOOTER_API UTriggerCapsuleComponent : public UCapsuleComponent, public ITrigger
{
	GENERATED_BODY()

public:
	UTriggerCapsuleComponent()
	{
		OnComponentBeginOverlap.AddDynamic(this, &UTriggerCapsuleComponent::BeginOverlap);
		OnComponentEndOverlap.AddDynamic(this, &UTriggerCapsuleComponent::EndOverlap);
	}
	
};
