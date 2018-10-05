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
	FTimerHandle Handler;
	GetWorld()->GetTimerManager().SetTimer(Handler, this, &AUnrealArcheryShooterGameMode::ApplyPlayerHUD, 1.0f, false, 1.0f);
	ApplyPlayerHUD();
}

void AUnrealArcheryShooterGameMode::ApplyPlayerHUD() {
	if (ApplyNewHUD(PlayerHUD, false, false))
	{
		//Cast<UPlayerHUD>(PlayerHUD.GetDefaultObject())->FillItemsInGrid(GetWorld());
		APlayerController* Player = GetWorld()->GetFirstPlayerController();
		Player->SetInputMode(FInputModeGameOnly());
		Player->SetIgnoreMoveInput(false);
		Player->SetIgnoreLookInput(false);
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
