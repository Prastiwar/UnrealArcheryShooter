// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "Cooldown/CooldownData.h"
#include "Cooldown.generated.h"

UCLASS()
class UNREALARCHERYSHOOTER_API UCooldown : public UObject
{
	GENERATED_BODY()

public:
	TArray<FCooldownData*> CooldownDatas;

	void SetCooldown(FCooldownData* CooldownData);
	void Complete(FCooldownData* CooldownData);
	void ResetTime(FCooldownData* CooldownData);

	UFUNCTION(BlueprintCallable)
		void Tick(float DeltaSeconds);

};
