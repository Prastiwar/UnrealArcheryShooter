// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "GameFramework/SaveGame.h"
#include "UnrealArcheryShooterGameMode.h"
#include "Game/UASCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "SaveState.generated.h"

UCLASS()
class UNREALARCHERYSHOOTER_API USaveState : public USaveGame
{
	GENERATED_BODY()
	
public:
	USaveState();

	static USaveState* Get()
	{
		return Cast<USaveState>(UGameplayStatics::CreateSaveGameObject(USaveState::StaticClass()));
	}

	static bool Save(USaveState* SaveState)
	{
		return UGameplayStatics::SaveGameToSlot(SaveState, SaveState->SlotName, SaveState->UserIndex);
	}

	static USaveState* Load()
	{
		USaveState* SaveState = Get();
		SaveState = Cast<USaveState>(UGameplayStatics::LoadGameFromSlot(SaveState->SlotName, SaveState->UserIndex));
		return SaveState;
	}

	void SavePlayer(AUASCharacter* Player);
	void LoadPlayer(AUASCharacter* Player);

private:
	UPROPERTY(EditAnywhere)
		FString SlotName;

	UPROPERTY(EditAnywhere)
		int32 UserIndex;

	UPROPERTY(VisibleAnywhere)
		FVector PlayerLocation;

	UPROPERTY(VisibleAnywhere)
		FQuat PlayerRotation;

	UPROPERTY(VisibleAnywhere)
		float PlayerScore;

	UPROPERTY(VisibleAnywhere)
		TArray<FWeaponData> PlayerWeapons;
	
};
