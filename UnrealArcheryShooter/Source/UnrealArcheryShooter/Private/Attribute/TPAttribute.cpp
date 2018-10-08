// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "TPAttribute.h"

UTPAttribute::UTPAttribute()
{
}

void UTPAttribute::Recalculate()
{
	Value = BaseValue;
	Modifiers.Sort();

	for (FTPModifier& Modifier : Modifiers)
	{
		switch (Modifier.Type)
		{
			case ModifierType::FlatIncrease:
				Value += Modifier.Value;
				break;

			case ModifierType::FlatMultiply:
				Value *= Modifier.Value;
				break;

			case ModifierType::Percentage:
				Value *= 1 + Modifier.Value;
				break;
		}
	}
	OnChanged.Broadcast(Value);
}

float UTPAttribute::GetValue()
{
	return Value;
}

float UTPAttribute::GetBaseValue()
{
	return BaseValue;
}

void UTPAttribute::SetBaseValue(float NewValue)
{
	BaseValue = NewValue;
	Recalculate();
}
