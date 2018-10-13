// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "CooldownComponent.h"

void UCooldownComponent::SetCooldown(FCooldownData* CooldownData)
{
	CooldownData->bIsCompleted = false;
	ResetTime(CooldownData);
	const int32 ID = CooldownDatas.Add(CooldownData);
	CooldownData->ID = ID;
}

void UCooldownComponent::Tick(float DeltaSeconds)
{
	for (uint8 Index = 0; Index < CooldownDatas.Num(); Index++)
	{
		if (CooldownDatas.IsValidIndex(Index))
		{
			FCooldownData* CD = CooldownDatas[Index];
			CD->CooldownTime -= DeltaSeconds * CD->TickRateMultiplier;
			if (CD->OnValueChanged.IsBound())
			{
				CD->OnValueChanged.Broadcast(CD->CooldownTime);
			}
			if (CD->CooldownTime <= 0.0f)
			{
				Complete(CD);
				Index--;
			}
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
