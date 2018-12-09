// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "SaveState.h"
#include "UnrealArcheryShooterGameMode.h"
#include "UASCharacter.h"
#include "WeaponComponent.h"

USaveState::USaveState()
{
	SlotName = TEXT("Slot0");
	UserIndex = 0;
}

void USaveState::SavePlayer(AUASCharacter* Player)
{
	PlayerLocation = Player->GetActorLocation();
	PlayerRotation = Player->GetActorQuat();
	PlayerWeapons = Player->GetWeaponComponent()->GetWeapons();
	PlayerScore = Player->GetScore();
}

void USaveState::LoadPlayer(AUASCharacter* Player) const
{
	Player->GetWeaponComponent()->SetWeapons(PlayerWeapons);
	Player->SetActorLocation(PlayerLocation);
	Player->GetController()->SetControlRotation(FRotator(PlayerRotation));
	Player->SetScore(PlayerScore);
	AUnrealArcheryShooterGameMode::GetUASGameMode(Player->GetWorld())->ApplyPlayerHUD();
}
