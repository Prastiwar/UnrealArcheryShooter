// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "WeaponShop.h"

void AWeaponShop::BuildShop()
{
	GLog->Log(TEXT("build start"));
	SetUIInput();

	UItemGrid* ItemGrid = ShopHud->GetDefaultObject<UItemGrid>();
	GLog->Log(ItemGrid->Grid ? TEXT("grid1 true") : TEXT("grid1 false"));

	TArray<UWeaponShopItem*> ItemWidgets = ItemGrid->FillItemGrid<UWeaponShopItem>();
	TArray<FUIWeaponData*> Weapons = GetItemsArray<FUIWeaponData>();
	uint8 WeaponsCount = Weapons.Num();
	uint32 WidgetsCount = ItemWidgets.Num();

	GLog->Log(FString::FromInt(ItemWidgets.Num()));
	if (WidgetsCount >= WeaponsCount)
	{
		for (uint8 Index = 0; Index < WeaponsCount; Index++)
		{
			ItemWidgets[Index]->SetShopItem(Weapons[Index]->Icon,
										FText::AsCurrency(Weapons[Index]->Cost),
										FText::FromName(Weapons[Index]->Weapon.Name));
		}
	}
	GLog->Log(ItemGrid->Grid ? TEXT("grid1 true") : TEXT("grid1 false"));
	GLog->Log(TEXT("build end"));
}

void AWeaponShop::SetUIInput()
{
	APlayerController* Player = GetWorld()->GetFirstPlayerController();
	Player->SetInputMode(FInputModeUIOnly());
	Player->SetIgnoreMoveInput(true);
	Player->SetIgnoreLookInput(true);
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
