// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "UnrealArcheryShooterGameMode.h"
#include "CoreGame/UASCharacter.h"

AUnrealArcheryShooterGameMode::AUnrealArcheryShooterGameMode() : Super()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/UnrealArcheryContent/Blueprints/Player/BP_UASFPP"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
	HUDClass = AUASHUD::StaticClass();
}

void AUnrealArcheryShooterGameMode::BeginPlay()
{
	Super::BeginPlay();
	ApplyPlayerHUD();
}

void AUnrealArcheryShooterGameMode::ApplyPlayerHUD()
{
	if (ApplyNewHUD(PlayerHUD, false, false))
	{
		APlayerController* Player = GetWorld()->GetFirstPlayerController();
		Player->SetInputMode(FInputModeGameOnly());
		Player->SetIgnoreMoveInput(false);
		Player->SetIgnoreLookInput(false);

		AUASCharacter* UASCharacter = AUASCharacter::GetUASCharacter(GetWorld());
		UASCharacter->OnWeaponChanged.AddDynamic(Cast<UPlayerHUD>(CurrentWidget), &UPlayerHUD::SetDirty);
		UASCharacter->OnScoreChanged.AddDynamic(Cast<UPlayerHUD>(CurrentWidget), &UPlayerHUD::RefreshScore);
		UASCharacter->AddScore(0); // refresh Score Text
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Applying Player HUD failed!"))
	}
}

bool AUnrealArcheryShooterGameMode::ApplyNewHUD(TSubclassOf<UUserWidget> Hud, const bool bShowCursor, const bool bEnableClickEvents)
{
	if (CurrentWidget)
	{
		CurrentWidget->RemoveFromParent();
	}
	if (GetWorld())
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), Hud);
		if (CurrentWidget)
		{
			APlayerController* const Controller = GetWorld()->GetFirstPlayerController();
			Controller->bShowMouseCursor = bShowCursor;
			Controller->bEnableClickEvents = bEnableClickEvents;
			CurrentWidget->AddToViewport();
			return true;
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Applying Player HUD error - No World detected"))
	}
	return false;
}
