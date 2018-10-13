// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "TPAttribute.h"

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

void UTPAttribute::SetBaseValue(const float NewValue)
{
	BaseValue = NewValue;
	Recalculate();
}

int32 UTPAttribute::Add(const FTPModifier& Modifier)
{
	int32 Index = Modifiers.Add(Modifier); 
	Recalculate();
	return Index;
}
