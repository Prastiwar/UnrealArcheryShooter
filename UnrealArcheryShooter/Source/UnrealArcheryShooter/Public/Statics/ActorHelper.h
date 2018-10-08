// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "CoreMinimal.h"

struct UNREALARCHERYSHOOTER_API FActorHelper
{
	/** If false, actor is hidden in game with disabled tick and collision*/
	static FORCEINLINE void SetActive(AActor* Actor, bool Active)
	{
		Actor->SetActorHiddenInGame(!Active);
		Actor->SetActorEnableCollision(Active);
		Actor->SetActorTickEnabled(Active);
	}
};
