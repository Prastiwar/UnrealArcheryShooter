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

void UWeaponShopGrid::SetGrid(TArray<UWeaponShopItem*> WeaponWidgetItems)
{
	if (AUnrealArcheryShooterGameMode::SetUIInput(GetWorld()))
	{
		AUASCharacter* Player = AUASCharacter::GetUASCharacter(GetWorld());
		// Weapons From Data Table
		TArray<FUIWeaponData*> Weapons = WeaponShop->GetDefaultObject<AWeaponShop>()->GetItemsArray<FUIWeaponData>();

		uint8 WeaponsCount = Weapons.Num();
		uint8 WidgetsCount = WeaponWidgetItems.Num();

		if (WeaponsCount <= WidgetsCount)
		{
			uint8 WidgetIndex = 0;
			for (uint8 WeaponIndex = 0; WeaponIndex < WeaponsCount; WeaponIndex++)
			{
				if (!Player->HasWeapon(Weapons[WeaponIndex]->Weapon))
				{
					WeaponWidgetItems[WidgetIndex]->SetShopItem(Weapons[WeaponIndex]->Icon,
						FText::FromName(Weapons[WeaponIndex]->Weapon.Name),
						FText::AsNumber(Weapons[WeaponIndex]->Cost));
					WeaponWidgetItems[WidgetIndex]->SetButton(WeaponIndex, WeaponShop);
					WeaponWidgetItems[WidgetIndex]->OnBuy.AddDynamic(this, &UWeaponShopGrid::TryExitShop);
					WidgetIndex++;
				}
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("WeaponShopGrid: There is more weapons than item widgets!"));
		}
	}
}