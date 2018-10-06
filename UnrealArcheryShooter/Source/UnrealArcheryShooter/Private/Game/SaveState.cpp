// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "SaveState.h"

USaveState::USaveState()
{
	SlotName = TEXT("Slot0");
	UserIndex = 0;
}

void USaveState::SavePlayer(AUASCharacter* Player)
{
	PlayerLocation = Player->GetActorLocation();
	PlayerRotation = Player->GetActorQuat();
	PlayerWeapons = Player->GetWeapons();
	PlayerScore = Player->GetScore();
}

void USaveState::LoadPlayer(AUASCharacter* Player)
{
	Player->SetWeapons(PlayerWeapons); 
	Player->SetActorLocation(PlayerLocation);
	Player->GetController()->SetControlRotation(FRotator(PlayerRotation));
	Player->SetScore(PlayerScore);
	AUnrealArcheryShooterGameMode::GetUASGameMode(Player->GetWorld())->ApplyPlayerHUD();
}
