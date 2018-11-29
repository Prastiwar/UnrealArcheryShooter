// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "PlayerHUD.h"
#include "Cooldown/CooldownData.h"
#include "UMG/Public/Components/TextBlock.h"

void UPlayerHUD::BuildGrid()
{
	RebuildGrid<UWeaponItem>(FilledWeaponItems);
	SetGrid(FilledWeaponItems);
}

void UPlayerHUD::OnDirty_Implementation()
{
	Super::OnDirty_Implementation(); // temporarily use old behavior
	// TODO: Change select and add new weapon item if needed

	//AUASCharacter* Player = AUASCharacter::GetUASCharacter(GetWorld());
	//ActualSelectedIndex = Player->GetWeaponComponent()->GetCurrentWeaponIndex();
	//SetSelection(ActualSelectedIndex);
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
	ActualSelectedIndex = NewSelectIndex;
	FilledWeaponItems[ActualSelectedIndex]->SetItemSelection(true);
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
			continue;
		}

		const FUIWeaponData* UIWeapon = WeaponsTable->FindRow<FUIWeaponData>(PlayerWeapons[Index].Name, TEXT(""));
		if (UIWeapon)
		{
			const bool bSelect = Index == ActualSelectedIndex;
			GridWeaponItems[Index]->SetItem(UIWeapon->Icon, bSelect);

			auto SetProgressPercentageLambda = [=](float Value) {
				GridWeaponItems[Index]->SetProgressPercentage(Value);
			};
			PlayerWeapons[Index].FireCooldown.OnValueChanged.RemoveAll(this);
			FDelegateHandle Handle = PlayerWeapons[Index].FireCooldown.OnValueChanged.AddLambda(SetProgressPercentageLambda);
		}
	}
}
