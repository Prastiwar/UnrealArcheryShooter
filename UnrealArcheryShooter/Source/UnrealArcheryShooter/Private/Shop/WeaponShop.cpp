// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "WeaponShop.h"

bool AWeaponShop::BuyItem(const UObject* WorldContextObject, int Index)
{
	TArray<FUIWeaponData*> Weapons = GetItemsArray<FUIWeaponData>();
	if (Weapons.IsValidIndex(Index))
	{
		AUASCharacter* Player = AUASCharacter::GetUASCharacter(WorldContextObject->GetWorld());
		if (Player->GetScore() >= Weapons[Index]->Cost)
		{
			Player->AddScore(-Weapons[Index]->Cost);
			Player->AddWeapon(Weapons[Index]->Weapon);
			if (SuccessSound != NULL)
			{
				UGameplayStatics::PlaySoundAtLocation(WorldContextObject, SuccessSound, GetActorLocation());
			}
			return true;
		}
	}
	if (FailSound != NULL)
	{
		UGameplayStatics::PlaySoundAtLocation(WorldContextObject, FailSound, GetActorLocation());
	}
	return false;
}
