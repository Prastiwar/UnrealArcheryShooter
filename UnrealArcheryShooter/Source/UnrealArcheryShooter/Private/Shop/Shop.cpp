// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "Shop.h"
#include "UI/ItemGrid.h"

AShop::AShop()
{
	PrimaryActorTick.bCanEverTick = false;
	BoxTrigger = SetTrigger<UBoxComponent>("Box Trigger");
	RootComponent = BoxTrigger;
}

void AShop::BeginPlay()
{
	Super::BeginPlay();
	PlayerCharacter = Cast<AUASCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	GameMode = GetWorld()->GetAuthGameMode<AUnrealArcheryShooterGameMode>();
}

void AShop::BeginTrigger(AActor* OtherActor)
{
	if (Cast<AUASCharacter>(OtherActor))
	{
		GameMode->ApplyNewHUD(ShopHud, true, true);
	}
}

void AShop::EndTrigger(AActor* OtherActor)
{
	if (Cast<AUASCharacter>(OtherActor))
	{
		GameMode->ApplyPlayerHUD();
	}
}
