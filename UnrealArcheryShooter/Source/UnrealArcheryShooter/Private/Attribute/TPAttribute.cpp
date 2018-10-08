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
			case EModifierType::FlatIncrease:
				Value += Modifier.Value;
				break;

			case EModifierType::FlatMultiply:
				Value *= Modifier.Value;
				break;

			case EModifierType::Percentage:
				Value *= 1 + Modifier.Value;
				break;
		}
	}
	OnChanged.Broadcast(Value);
}

void UTPAttribute::SetBaseValue(float NewValue)
{
	BaseValue = NewValue;
	Recalculate();
}
