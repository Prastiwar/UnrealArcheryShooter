// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "PlayerHUD.h"

void UPlayerHUD::FillGrid()
{
	TArray<UWeaponItem*> WeaponItems = FillItemGrid<UWeaponItem>();
	SetGrid(WeaponItems);
}

void UPlayerHUD::RefreshScore(float Score)
{
	FNumberFormattingOptions options = FNumberFormattingOptions();
	options.SetMaximumFractionalDigits(0);
	ScoreText->SetText(FText::AsNumber(Score, &options));
}

void UPlayerHUD::SetGrid(TArray<UWeaponItem*> WeaponItems)
{
	if (AUASCharacter* Player = AUASCharacter::GetUASCharacter(GetWorld()))
	{
		TArray<FWeaponData> PlayerWeapons = Player->GetWeapons();
		for (uint8 Index = 0; Index < WeaponItems.Num(); Index++)
		{
			if (PlayerWeapons.IsValidIndex(Index))
			{
				FUIWeaponData* UIWeapon = WeaponsTable->FindRow<FUIWeaponData>(PlayerWeapons[Index].Name, TEXT(""));
				if (UIWeapon)
				{
					int SelectedWeaponIndex = Player->GetCurrentWeaponIndex();
					bool bSelect = Index == SelectedWeaponIndex;
					WeaponItems[Index]->SetItem(UIWeapon->Icon, bSelect);
				}
			}
		}
	}
}
