// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "AcceleratedSpawnerComponent.h"

UAcceleratedSpawnerComponent::UAcceleratedSpawnerComponent()
{
	SpawnTimeLimitRange = FVector2D(0.1f, 5.0f);
	TimeToChangeFrequency = 30;
	ChangeFrequencyAmount = 0.1f;
	bSetFrequencyTimerOnBeginPlay = true;
}

void UAcceleratedSpawnerComponent::BeginPlay()
{
	Super::BeginPlay();
	if (bSetFrequencyTimerOnBeginPlay)
	{
		SetTimer();
	}
}

void UAcceleratedSpawnerComponent::ChangeFrequency()
{
	CooldownData.InitialTime = FMath::Clamp(CooldownData.InitialTime - ChangeFrequencyAmount, SpawnTimeLimitRange.X, SpawnTimeLimitRange.Y);
	if (CooldownData.InitialTime <= SpawnTimeLimitRange.X || CooldownData.InitialTime >= SpawnTimeLimitRange.Y)
	{
		GetWorld()->GetTimerManager().ClearTimer(FrequencyTimerHandle);
	}
	//SetTimer();
}

void UAcceleratedSpawnerComponent::SetTimer()
{
	GetWorld()->GetTimerManager().SetTimer(
		FrequencyTimerHandle,
		this,
		&UAcceleratedSpawnerComponent::ChangeFrequency,
		UAcceleratedSpawnerComponent::TimeToChangeFrequency,
		true,
		UAcceleratedSpawnerComponent::TimeToChangeFrequency
	);
}
