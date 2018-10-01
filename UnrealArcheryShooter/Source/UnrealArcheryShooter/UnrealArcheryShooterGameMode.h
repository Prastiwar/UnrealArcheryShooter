// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PlayerHUDBuilder.h"
#include "UnrealArcheryShooterGameMode.generated.h"

UCLASS()
class UNREALARCHERYSHOOTER_API AUnrealArcheryShooterGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AUnrealArcheryShooterGameMode();

	bool ApplyNewHUD(TSubclassOf<class UUserWidget> Hud, bool bShowCursor, bool bEnableEvents);
	void ApplyPlayerHUD() { ApplyNewHUD(PlayerHUDBuilder->GetDefaultObject<UPlayerHUDBuilder>()->GetPlayerHUD(), false, false); }
	UUserWidget* GetCurrentWidget() { return CurrentWidget; }

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UPlayerHUDBuilder> PlayerHUDBuilder;

	UPROPERTY(BlueprintReadWrite)
		UUserWidget* CurrentWidget;

};
