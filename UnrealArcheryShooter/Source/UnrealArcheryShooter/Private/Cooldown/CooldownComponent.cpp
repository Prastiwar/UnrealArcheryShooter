// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "CooldownComponent.h"

UCooldownComponent::UCooldownComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCooldownComponent::SetCooldown(FCooldownData* CooldownData)
{
	CooldownData->bIsCompleted = false;
	ResetTime(CooldownData);
	const int32 ID = CooldownDatas.Add(CooldownData);
	CooldownData->ID = ID;
}

void UCooldownComponent::Complete(FCooldownData* CooldownData)
{
	CooldownData->bIsCompleted = true;
	if (CooldownData->OnCompleted.IsBound())
	{
		CooldownData->OnCompleted.Broadcast();
	}
	ResetTime(CooldownData);
	CooldownDatas.RemoveSingleSwap(CooldownData, false);
}

void UCooldownComponent::ResetTime(FCooldownData* CooldownData)
{
	CooldownData->CooldownTime = CooldownData->InitialTime;
}

void UCooldownComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	for (int8 Index = CooldownDatas.Num() - 1; Index >= 0; Index--)
	{
		FCooldownData* CD = CooldownDatas[Index];
		CD->CooldownTime -= DeltaTime * CD->TickRateMultiplier;
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
