// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "CPPLearnGameMode.h"
#include "CPPLearnHUD.h"
#include "CPPLearnCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"

ACPPLearnGameMode::ACPPLearnGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ACPPLearnHUD::StaticClass();
}

void ACPPLearnGameMode::BeginPlay()
{
	Super::BeginPlay();
	ACPPLearnCharacter* FPPCharacter = Cast<ACPPLearnCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (PlayerHUD)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUD);
		if (CurrentWidget)
		{
			CurrentWidget->AddToViewport();
		}
	}
}
