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
	if (PlayerHUD)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUD);
		CurrentWidget->AddToViewport();
	}
}
