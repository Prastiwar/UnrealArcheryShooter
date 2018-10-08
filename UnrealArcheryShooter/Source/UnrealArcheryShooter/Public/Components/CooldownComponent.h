// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "Engine.h"
#include "Data/CooldownData.h"
#include "CooldownComponent.generated.h"

UCLASS()
class UNREALARCHERYSHOOTER_API UCooldownComponent : public UObject
{
	GENERATED_BODY()

public:
	UCooldownComponent();

	TArray<FCooldownData*> CooldownDatas;

	void SetCooldown(FCooldownData* CooldownData);
	void Complete(FCooldownData* CooldownData);
	void ResetTime(FCooldownData* CooldownData);

	UFUNCTION(BlueprintCallable)
		void Tick(float DeltaSeconds);

};
