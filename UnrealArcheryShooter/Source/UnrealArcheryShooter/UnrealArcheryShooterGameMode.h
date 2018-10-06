// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "GameFramework/GameModeBase.h"
#include "Game/UASCharacter.h"
#include "UI/PlayerHUD.h"
#include "UASHUD.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"
#include "UnrealArcheryShooterGameMode.generated.h"

UCLASS()
class UNREALARCHERYSHOOTER_API AUnrealArcheryShooterGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AUnrealArcheryShooterGameMode();

	static AUnrealArcheryShooterGameMode* GetUASGameMode(const UWorld* World)
	{
		return World ? World->GetAuthGameMode<AUnrealArcheryShooterGameMode>() : nullptr;
	}
	
	static bool SetUIInput(const UWorld* World)
	{
		if (World)
		{
			if (APlayerController* Player = World->GetFirstPlayerController())
			{
				Player->SetInputMode(FInputModeUIOnly());
				Player->SetIgnoreMoveInput(true);
				Player->SetIgnoreLookInput(true);
				return true;
			}
		}
		return false;
	}

	void ApplyPlayerHUD();
	bool ApplyNewHUD(TSubclassOf<class UUserWidget> Hud, bool bShowCursor, bool bEnableClickEvents);
	UUserWidget* GetCurrentWidget() { return CurrentWidget; }

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> PlayerHUD;

	UPROPERTY(BlueprintReadWrite)
		UUserWidget* CurrentWidget;

};
