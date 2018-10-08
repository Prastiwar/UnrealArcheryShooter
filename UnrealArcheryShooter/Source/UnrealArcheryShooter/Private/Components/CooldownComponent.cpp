// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "CooldownComponent.h"

UCooldownComponent::UCooldownComponent()
{
}

void UCooldownComponent::SetCooldown(FCooldownData* CooldownData)
{
	CooldownData->bIsCompleted = false;
	ResetTime(CooldownData);
	CooldownDatas.Add(CooldownData);
}

void UCooldownComponent::Tick(float DeltaSeconds)
{
	for (uint8 Index = 0; Index < CooldownDatas.Num(); Index++)
	{
		CooldownDatas[Index]->CooldownTime -= DeltaSeconds * CooldownDatas[Index]->TickRateMultiplier;
		if (CooldownDatas[Index]->CooldownTime <= 0.0f)
		{
			Complete(CooldownDatas[Index]);
			Index--;
		}
	}
}

void UCooldownComponent::Complete(FCooldownData* CooldownData)
{
	CooldownData->bIsCompleted = true;
	ResetTime(CooldownData);
	CooldownDatas.RemoveSingleSwap(CooldownData, false);
}

void UCooldownComponent::ResetTime(FCooldownData* CooldownData)
{
	CooldownData->CooldownTime = CooldownData->InitialTime;
}