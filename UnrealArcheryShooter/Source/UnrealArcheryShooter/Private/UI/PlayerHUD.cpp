// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "PlayerHUD.h"
#include "UI/WeaponItem.h"
#include "UMG/Public/Components/TextBlock.h"

void UPlayerHUD::FillGrid()
{
	TArray<UWeaponItem*> WeaponItems = FillItemGrid<UWeaponItem>();
	SetGrid(WeaponItems);
}

void UPlayerHUD::RefreshScore(const float Score)
{
	FNumberFormattingOptions options = FNumberFormattingOptions();
	options.SetMaximumFractionalDigits(0);
	ScoreText->SetText(FText::AsNumber(Score, &options));
}

void UPlayerHUD::SetGrid(TArray<UWeaponItem*>& WeaponItems)
{
	AUASCharacter* Player = AUASCharacter::GetUASCharacter(GetWorld());
	if (!Player)
	{
		return;
	}

	TArray<FWeaponData>* PlayerWeaponsPtr = Player->GetWeaponsPtr();
	for (uint8 Index = 0; Index < WeaponItems.Num(); Index++)
	{
		if (!PlayerWeaponsPtr->IsValidIndex(Index))
		{
			continue;
		}

		FWeaponData& PlayerWeapon = PlayerWeaponsPtr->operator [](Index);
		const FUIWeaponData* UIWeapon = WeaponsTable->FindRow<FUIWeaponData>(PlayerWeapon.Name, TEXT(""));
		if (UIWeapon)
		{
			const int SelectedWeaponIndex = Player->GetCurrentWeaponIndex();
			const bool bSelect = Index == SelectedWeaponIndex;
			WeaponItems[Index]->SetItem(UIWeapon->Icon, bSelect);

			auto Lambda = [WeaponItems, Index](float Value) {
				WeaponItems[Index]->SetProgressPercentage(Value);
			};
			PlayerWeapon.FireCooldown.OnValueChanged.AddLambda(Lambda);
		}
	}
}
