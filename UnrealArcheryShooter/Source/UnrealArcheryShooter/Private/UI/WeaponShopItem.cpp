// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "WeaponShopItem.h"

void UWeaponShopItem::SetShopItem(UTexture2D* Icon, FText Name, FText Cost)
{
	ItemImage->SetBrushFromTexture(Icon);
	ItemName->SetText(Name);
	ItemCost->SetText(Cost);
}
