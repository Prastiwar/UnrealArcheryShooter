// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "WeaponShop.h"

void AWeaponShop::BuildShop()
{
	UItemGrid* ItemGrid = ShopHud->GetDefaultObject<UItemGrid>();
	ItemGrid->bAutoFill = false;
	GLog->Log(FString::FromInt(ItemGrid->RowCount));
	GLog->Log(ItemGrid->ItemWidgetClass ? TEXT("true") : TEXT("false"));
	GLog->Log(ItemGrid->Grid ? TEXT("true") : TEXT("false"));
	TArray<UItemWidget*> ItemWidgets = ItemGrid->FillGrid<UItemWidget>();
	TArray<FUIWeaponData*> Weapons = GetItemsArray<FUIWeaponData>();
	uint8 WeaponsCount = Weapons.Num();
	uint32 WidgetsCount = ItemWidgets.Num();
	GLog->Log(FString::FromInt(ItemWidgets.Num()));
	if (WidgetsCount >= WeaponsCount)
	{
		for (uint8 Index = 0; Index < WeaponsCount; Index++)
		{
			ItemWidgets[Index]->SetItem(Weapons[Index]->Icon, FText::AsCurrency(Weapons[Index]->Cost), Weapons[Index]->Weapon.Name);
		}
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
