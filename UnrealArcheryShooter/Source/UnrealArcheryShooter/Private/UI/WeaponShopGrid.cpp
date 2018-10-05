// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "WeaponShopGrid.h"

void UWeaponShopGrid::NativeConstruct()
{
	Super::NativeConstruct();
	if (ExitButton)
	{
		ExitButton->OnClicked.AddDynamic(this, &UWeaponShopGrid::ExitShop);
	}
}

void UWeaponShopGrid::ExitShop()
{
	GetWorld()->GetAuthGameMode<AUnrealArcheryShooterGameMode>()->ApplyPlayerHUD();
}

void UWeaponShopGrid::TryExitShop(bool bBought)
{
	if (bBought)
	{
		GetWorld()->GetAuthGameMode<AUnrealArcheryShooterGameMode>()->ApplyPlayerHUD();
	}
}

void UWeaponShopGrid::FillGrid()
{
	TArray<UWeaponShopItem*> WeaponItems = FillItemGrid<UWeaponShopItem>();
	SetGrid(WeaponItems);
}

void UWeaponShopGrid::SetGrid(TArray<UWeaponShopItem*> WeaponItems)
{
	if (AUnrealArcheryShooterGameMode::SetUIInput(GetWorld()))
	{
		TArray<FUIWeaponData*> Weapons = WeaponShop->GetDefaultObject<AWeaponShop>()->GetItemsArray<FUIWeaponData>();
		uint8 WeaponsCount = Weapons.Num();
		uint32 WidgetsCount = WeaponItems.Num();
		for (uint8 Index = 0; Index < WeaponsCount; Index++)
		{
			WeaponItems[Index]->SetShopItem(Weapons[Index]->Icon,
				FText::FromName(Weapons[Index]->Weapon.Name),
				FText::AsNumber(Weapons[Index]->Cost));
			WeaponItems[Index]->SetButton(Index, WeaponShop);
			WeaponItems[Index]->OnBuy.AddDynamic(this, &UWeaponShopGrid::TryExitShop);
		}
	}
}