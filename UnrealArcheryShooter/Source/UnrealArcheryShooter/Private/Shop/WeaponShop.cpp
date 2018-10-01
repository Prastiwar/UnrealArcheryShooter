// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "WeaponShop.h"

void AWeaponShop::BuildShop()
{
	TArray<FUIWeaponData*> Weapons = GetItemsArray<FUIWeaponData>();
	uint8 Count = Weapons.Num();
	for (uint8 i = 0; i < Count; i++)
	{
		// create slot
		//Weapons[i]->Cost;
		//Weapons[i]->Icon;
		//Weapons[i]->Weapon.Name;
		//WeaponItem->GetDefaultObject<UUserWidget>().
		//ShopHud->
	}
}

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
