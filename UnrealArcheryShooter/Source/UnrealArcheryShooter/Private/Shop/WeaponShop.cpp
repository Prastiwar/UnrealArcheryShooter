// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "WeaponShop.h"

bool AWeaponShop::BuyItem(const UObject* WorldContextObject, const int32 WeaponIndex)
{
	const TArray<FUIWeaponData*> Weapons = GetItemsArray<FUIWeaponData>();
	if (Weapons.IsValidIndex(WeaponIndex))
	{
		AUASCharacter* const Player = AUASCharacter::GetUASCharacter(WorldContextObject->GetWorld());
		if (Player->GetScore() >= Weapons[WeaponIndex]->Cost)
		{
			Player->AddScore(-Weapons[WeaponIndex]->Cost);
			Player->AddWeapon(Weapons[WeaponIndex]->Weapon);
			FActorHelper::SafePlaySound(WorldContextObject, SuccessSound, GetActorLocation());
			return true;
		}
	}
	FActorHelper::SafePlaySound(WorldContextObject, FailSound, GetActorLocation());
	return false;
}
