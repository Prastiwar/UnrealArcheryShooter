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

	TArray<FWeaponData>* PlayerWeaponsPtr = Player->GetWeaponComponent()->GetWeaponsPtr();
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
			const int32 SelectedWeaponIndex = Player->GetWeaponComponent()->GetCurrentWeaponIndex();
			const bool bSelect = Index == SelectedWeaponIndex;
			WeaponItems[Index]->SetItem(UIWeapon->Icon, bSelect);

			auto SetProgressPercentage = [=](float Value) {
				WeaponItems[Index]->SetProgressPercentage(Value);
			};
			PlayerWeapon.FireCooldown.OnValueChanged.AddLambda(SetProgressPercentage); // FIXME: fix adding same, new action every time
		}
	}
}
