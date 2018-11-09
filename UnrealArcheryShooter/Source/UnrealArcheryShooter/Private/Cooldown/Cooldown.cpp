// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "Cooldown.h"

void UCooldown::SetCooldown(FCooldownData* CooldownData)
{
	CooldownData->bIsCompleted = false;
	ResetTime(CooldownData);
	const int32 ID = CooldownDatas.Add(CooldownData);
	CooldownData->ID = ID;
}

void UCooldown::Tick(float DeltaSeconds)
{
	for (int8 Index = CooldownDatas.Num() - 1; Index >= 0; Index--)
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

void UCooldown::Complete(FCooldownData* CooldownData)
{
	CooldownData->bIsCompleted = true;
	ResetTime(CooldownData);
	CooldownDatas.RemoveSingleSwap(CooldownData, false);
}

void UCooldown::ResetTime(FCooldownData* CooldownData)
{
	CooldownData->CooldownTime = CooldownData->InitialTime;
}
