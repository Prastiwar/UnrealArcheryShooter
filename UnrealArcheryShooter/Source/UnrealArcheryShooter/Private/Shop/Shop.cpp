// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "Shop.h"
#include "ItemGrid.h"

AShop::AShop()
{
	PrimaryActorTick.bCanEverTick = false;

	// TODO: Changeable shape
	TriggerShape = Cast<UShapeComponent>(CreateDefaultSubobject<UTriggerBoxComponent>(TEXT("TriggerShape")));
	RootComponent = TriggerShape;
	if (ITrigger* Trigger = Cast<ITrigger>(TriggerShape))
	{
		Trigger->BindTrigger(this, &AShop::BeginTrigger, &AShop::EndTrigger);
	}
}

void AShop::BeginPlay()
{
	Super::BeginPlay();
	GameMode = GetWorld()->GetAuthGameMode<AUnrealArcheryShooterGameMode>();
}

void AShop::BeginTrigger(AActor* OtherActor, UPrimitiveComponent* OtherComp)
{
	PlayerCharacter = Cast<AUASCharacter>(OtherActor);
	if (PlayerCharacter)
	{
		GameMode->ApplyNewHUD(ShopHud, true, true);
	}
}

void AShop::EndTrigger(AActor* OtherActor, UPrimitiveComponent* OtherComp)
{
	if (Cast<AUASCharacter>(OtherActor))
	{
		GameMode->ApplyPlayerHUD();
	}
}
