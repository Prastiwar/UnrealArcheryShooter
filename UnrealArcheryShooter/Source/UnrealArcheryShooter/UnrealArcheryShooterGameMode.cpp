// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "UnrealArcheryShooterGameMode.h"
#include "UASHUD.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"

AUnrealArcheryShooterGameMode::AUnrealArcheryShooterGameMode() : Super()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/UnrealArcheryContent/Blueprints/Player/BP_FirstPersonCharacter"));
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
	ApplyNewHUD(PlayerHUD, false, false);
}

bool AUnrealArcheryShooterGameMode::ApplyNewHUD(TSubclassOf<class UUserWidget> Hud, bool bShowCursor, bool bEnableEvents)
{
	if (CurrentWidget)
	{
		CurrentWidget->RemoveFromParent();
	}

	CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), Hud);
	if (CurrentWidget)
	{
		APlayerController* Controller = GetWorld()->GetFirstPlayerController();
		Controller->bShowMouseCursor = bShowCursor;
		Controller->bEnableClickEvents = bEnableEvents;
		CurrentWidget->AddToViewport();
		return true;
	}
	return false;
}
