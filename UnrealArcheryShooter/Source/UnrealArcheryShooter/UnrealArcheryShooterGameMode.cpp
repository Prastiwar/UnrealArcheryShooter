// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "UnrealArcheryShooterGameMode.h"
#include "UASHUD.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"

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

void AUnrealArcheryShooterGameMode::ApplyPlayerHUD() {
	if (ApplyNewHUD(PlayerHUD, false, false))
	{
		APlayerController* Player = GetWorld()->GetFirstPlayerController();
		Player->SetInputMode(FInputModeGameOnly());
		Player->SetIgnoreMoveInput(false);
		Player->SetIgnoreLookInput(false);
		AUASCharacter::GetUASCharacter(GetWorld())->OnWeaponChanged.AddDynamic(Cast<UPlayerHUD>(CurrentWidget), &UPlayerHUD::SetDirty);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Applying Player HUD failed!"))
	}
}

bool AUnrealArcheryShooterGameMode::ApplyNewHUD(TSubclassOf<class UUserWidget> Hud, bool bShowCursor, bool bEnableClickEvents)
{
	if (CurrentWidget)
	{
		CurrentWidget->RemoveFromParent();
	}
	if (GetWorld() == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Applying Player HUD NO WORLD"))
	}
	CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), Hud);
	if (CurrentWidget)
	{
		APlayerController* Controller = GetWorld()->GetFirstPlayerController();
		Controller->bShowMouseCursor = bShowCursor;
		Controller->bEnableClickEvents = bEnableClickEvents;
		CurrentWidget->AddToViewport();
		return true;
	}
	return false;
}
