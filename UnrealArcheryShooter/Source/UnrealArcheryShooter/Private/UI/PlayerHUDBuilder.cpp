// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "PlayerHUDBuilder.h"

UPlayerHUDBuilder::UPlayerHUDBuilder()
{
}

UPlayerHUDBuilder::~UPlayerHUDBuilder()
{
}

void UPlayerHUDBuilder::BuildWeaponSlotsWidget(uint8 Count)
{
	AUASCharacter* Player = Cast<AUASCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	TArray<FWeaponData> PlayerWeapons = Player->GetWeapons();
	int SelectedWeaponIndex = Player->GetCurrentWeaponIndex();

	for (uint8 i = 0; i < Count; i++)
	{
		//CreateWidget();

		if (PlayerWeapons.IsValidIndex(i))
		{
			//FUIWeaponData* UIWeapon = WeaponsTable->FindRow<FUIWeaponData>(FString(PlayerWeapons[i].Name), TEXT(""));
			//UIWeapon->Icon;
		}
	}
}
