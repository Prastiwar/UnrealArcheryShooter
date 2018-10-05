// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "ShopGrid.h"

void UShopGrid::NativeConstruct()
{
	Super::NativeConstruct();
	if (ExitButton)
	{
		ExitButton->OnClicked.AddDynamic(this, &UShopGrid::ExitShop);
	}
}

void UShopGrid::ExitShop()
{
	GetWorld()->GetAuthGameMode<AUnrealArcheryShooterGameMode>()->ApplyPlayerHUD();
}
