// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "UnrealArcheryShooterGameMode.generated.h"

class UASHUD;
class UPlayerHUD;

UCLASS()
class UNREALARCHERYSHOOTER_API AUnrealArcheryShooterGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AUnrealArcheryShooterGameMode();

	static FORCEINLINE AUnrealArcheryShooterGameMode* GetUASGameMode(const UWorld* World)
	{
		return World ? World->GetAuthGameMode<AUnrealArcheryShooterGameMode>() : nullptr;
	}

	static FORCEINLINE bool SetUIInput(const UWorld* World)
	{
		if (World)
		{
			if (APlayerController* const Player = World->GetFirstPlayerController())
			{
				Player->SetInputMode(FInputModeUIOnly());
				Player->SetIgnoreMoveInput(true);
				Player->SetIgnoreLookInput(true);
				return true;
			}
		}
		return false;
	}

	FORCEINLINE UUserWidget* GetCurrentWidget() const { return CurrentWidget; }

	void ApplyPlayerHUD();
	bool ApplyNewHUD(TSubclassOf<UUserWidget> Hud, const bool bShowCursor, const bool bEnableClickEvents);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TSubclassOf<UUserWidget> PlayerHUD;

	UPROPERTY(BlueprintReadOnly)
		UUserWidget* CurrentWidget;

};
