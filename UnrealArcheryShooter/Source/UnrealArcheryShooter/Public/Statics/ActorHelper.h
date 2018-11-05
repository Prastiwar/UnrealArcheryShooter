// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "Engine/Classes/Kismet/GameplayStatics.h"

struct UNREALARCHERYSHOOTER_API FActorHelper
{
	/** If false, actor is hidden in game with disabled tick and collision*/
	static FORCEINLINE void SetActive(AActor* Actor, const bool Active)
	{
		Actor->SetActorHiddenInGame(!Active);
		Actor->SetActorEnableCollision(Active);
		Actor->SetActorTickEnabled(Active);

		for (UActorComponent* Comp : Actor->GetComponents())
		{
			Comp->SetActive(Active);
		}
	}

	/** If false, actor is hidden in game with disabled tick and collision*/
	static FORCEINLINE void SafePlaySound(const UObject* WorldContext, USoundBase* Sound, const FVector Location,
		const float VolumeMultiplier = 1.0f, const float PitchMultiplier = 1.0f, const float StartTime = 0.0f)
	{
		if (Sound != NULL)
		{
			UGameplayStatics::PlaySoundAtLocation(WorldContext, Sound, Location, VolumeMultiplier, PitchMultiplier, StartTime);
		}
	}
};
