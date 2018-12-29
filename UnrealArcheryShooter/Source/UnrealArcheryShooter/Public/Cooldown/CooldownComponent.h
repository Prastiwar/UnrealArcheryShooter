// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "Components/ActorComponent.h"
#include "CooldownData.h"
#include "CooldownComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UNREALARCHERYSHOOTER_API UCooldownComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCooldownComponent();

	void SetCooldown(FCooldownData* CooldownData);

	void Complete(FCooldownData* CooldownData);

	void ResetTime(FCooldownData* CooldownData);


protected:
	TArray<FCooldownData*> CooldownDatas;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};
