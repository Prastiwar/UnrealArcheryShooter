// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "PlayerHUD.h"
#include "WeaponItem.h"
#include "CooldownData.h"
#include "WeaponComponent.h"
#include "UMG/Public/Components/TextBlock.h"

void UPlayerHUD::BuildGrid()
{
	RebuildGrid<UWeaponItem>(FilledWeaponItems);
	SetGrid(FilledWeaponItems);
}

void UPlayerHUD::OnDirty_Implementation()
{
	UWeaponComponent* PlayerWeaponComp = AUASCharacter::GetUASCharacter(GetWorld())->GetWeaponComponent();
	const int32 PlayerWeaponsNum = PlayerWeaponComp->GetWeaponsRef().Num();
	const int32 WeaponsInGridNum = FilledWeaponItems.IndexOfByPredicate([](UWeaponItem* Item) { return Item->IsEmpty(); });
	if (PlayerWeaponsNum != WeaponsInGridNum)
	{
		BuildGrid();
	}
	else
	{
		SetSelection(PlayerWeaponComp->GetCurrentWeaponIndex());
	}
}

void UPlayerHUD::RefreshScore(const float Score)
{
	FNumberFormattingOptions Options = FNumberFormattingOptions();
	Options.SetMaximumFractionalDigits(0);
	ScoreText->SetText(FText::AsNumber(Score, &Options));
}

void UPlayerHUD::SetNextSelection()
{
	SetSelection(ActualSelectedIndex + 1);
}

void UPlayerHUD::SetPreviousSelection()
{
	SetSelection(ActualSelectedIndex - 1);
}

void UPlayerHUD::SetSelection(int32 NewSelectIndex)
{
	if (NewSelectIndex >= FilledWeaponItems.Num())
	{
		NewSelectIndex = 0;
	}
	else if (NewSelectIndex < 0)
	{
		NewSelectIndex = FilledWeaponItems.Num() - 1;
	}
	FilledWeaponItems[ActualSelectedIndex]->SetItemSelection(false);
	FilledWeaponItems[NewSelectIndex]->SetItemSelection(true);
	ActualSelectedIndex = NewSelectIndex;
}

void UPlayerHUD::SetGrid(TArray<UWeaponItem*>& GridWeaponItems)
{
	AUASCharacter* Player = AUASCharacter::GetUASCharacter(GetWorld());
	if (!Player)
	{
		return;
	}

	TArray<FWeaponData>& PlayerWeapons = Player->GetWeaponComponent()->GetWeaponsRef();
	ActualSelectedIndex = Player->GetWeaponComponent()->GetCurrentWeaponIndex();

	for (uint8 Index = 0; Index < GridWeaponItems.Num(); Index++)
	{
		if (!PlayerWeapons.IsValidIndex(Index))
		{
			GridWeaponItems[Index]->SetItem(nullptr, false);
			continue;
		}

		const FUIWeaponData* UIWeapon = WeaponsTable->FindRow<FUIWeaponData>(PlayerWeapons[Index].Name, TEXT(""));
		if (UIWeapon)
		{
			const bool bSelect = Index == ActualSelectedIndex;
			GridWeaponItems[Index]->SetItem(UIWeapon->Icon, bSelect);

			PlayerWeapons[Index].FireCooldown.OnValueChanged.RemoveAll(this);
			PlayerWeapons[Index].FireCooldown.OnValueChanged.AddUObject(this, &UPlayerHUD::SetProgressFunc, GridWeaponItems[Index]);
		}
	}
}

void UPlayerHUD::SetProgressFunc(float Value, UWeaponItem* WeaponItem)
{
	WeaponItem->SetProgressPercentage(Value);
}
