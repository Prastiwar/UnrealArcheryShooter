// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "WeaponShop.h"

bool AWeaponShop::BuyItem(int Index)
{
	TArray<FUIWeaponData*> Weapons = GetItemsArray<FUIWeaponData>();
	if (Weapons.IsValidIndex(Index))
	{
		if (GetPlayerCharacter()->GetScore() >= Weapons[Index]->Cost)
		{
			GetPlayerCharacter()->AddScore(-Weapons[Index]->Cost);
			GetPlayerCharacter()->AddWeapon(Weapons[Index]->Weapon);
			return true;
		}
	}
	return false;
}
