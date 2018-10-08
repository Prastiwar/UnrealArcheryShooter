// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "WeaponShop.h"

bool AWeaponShop::BuyItem(const UObject* WorldContextObject, const int32 WeaponIndex)
{
	TArray<FUIWeaponData*> Weapons = GetItemsArray<FUIWeaponData>();
	if (Weapons.IsValidIndex(WeaponIndex))
	{
		AUASCharacter* Player = AUASCharacter::GetUASCharacter(WorldContextObject->GetWorld());
		if (Player->GetScore() >= Weapons[WeaponIndex]->Cost)
		{
			Player->AddScore(-Weapons[WeaponIndex]->Cost);
			Player->AddWeapon(Weapons[WeaponIndex]->Weapon);
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
