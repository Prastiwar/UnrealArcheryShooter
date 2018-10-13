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

void UWeaponShopGrid::TryExitShop(const bool bBought)
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

void UWeaponShopGrid::SetGrid(const TArray<UWeaponShopItem*>& WeaponWidgetItems)
{
	if (!AUnrealArcheryShooterGameMode::SetUIInput(GetWorld()))
	{
		return;
	}

	const TArray<FUIWeaponData*> DTWeapons = WeaponShop->GetDefaultObject<AWeaponShop>()->GetItemsArray<FUIWeaponData>();
	if (DTWeapons.Num() <= WeaponWidgetItems.Num())
	{
		AUASCharacter* Player = AUASCharacter::GetUASCharacter(GetWorld());
		uint8 WidgetIndex = 0; // We want set widget independently on order between Player Weapons and Weapons from DT
		for (uint8 DTWeaponIndex = 0; DTWeaponIndex < DTWeapons.Num(); DTWeaponIndex++)
		{
			const FUIWeaponData* UIWeapon = DTWeapons[DTWeaponIndex];
			const FWeaponData& Weapon = UIWeapon->Weapon;
			// Don't sell items that Player already has
			if (!Player->HasWeapon(Weapon))
			{
				WeaponWidgetItems[WidgetIndex]->SetShopItem(
					UIWeapon->Icon,
					FText::FromName(Weapon.Name),
					FText::AsNumber(UIWeapon->Cost),
					DTWeaponIndex,
					WeaponShop
				);
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