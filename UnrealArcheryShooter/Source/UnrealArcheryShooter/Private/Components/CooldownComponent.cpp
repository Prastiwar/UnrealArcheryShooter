// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "CooldownComponent.h"

UCooldownComponent::UCooldownComponent()
{
}

void UCooldownComponent::SetCooldown(FCooldownData &CooldownData)
{
	CooldownData.IsCompleted = false;
	ResetTime(CooldownData);
	CooldownDatas.Add(CooldownData);
}

void UCooldownComponent::Tick()
{
	float Delta = FApp::GetDeltaTime();
	uint8 Length = CooldownDatas.Num();

	for (uint8 Index = 0; Index < Length; Index++)
	{
		CooldownDatas[Index].CooldownTime -= Delta * CooldownDatas[Index].TickRateMultiplier;
		//GLog->Log(FString::SanitizeFloat(CooldownDatas[Index].CooldownTime));
		if (CooldownDatas[Index].CooldownTime <= 0.0f)
		{
			Complete(CooldownDatas[Index]);
		}
	}
}

void UCooldownComponent::Complete(FCooldownData &CooldownData)
{
	CooldownData.IsCompleted = true;
	ResetTime(CooldownData);
	CooldownDatas.RemoveSingle(CooldownData);
}

void UCooldownComponent::ResetTime(FCooldownData &CooldownData)
{
	CooldownData.CooldownTime = CooldownData.InitialTime;
}