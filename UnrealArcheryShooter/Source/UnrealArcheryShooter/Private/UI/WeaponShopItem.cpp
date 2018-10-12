// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "WeaponShopItem.h"

void UWeaponShopItem::SetShopItem(UTexture2D* Icon, FText Name, FText Cost, int DTWeaponIndex, TSubclassOf<class AWeaponShop> WeaponShop)
{
	ItemImage->SetBrushFromTexture(Icon);
	ItemName->SetText(Name);
	ItemCost->SetText(Cost);

	this->WeaponIndex = DTWeaponIndex;
	this->WeaponShop = WeaponShop;
	Button->OnClicked.AddDynamic(this, &UWeaponShopItem::Buy);
}

void UWeaponShopItem::Buy()
{
	OnBuy.Broadcast(WeaponShop->GetDefaultObject<AWeaponShop>()->BuyItem(this, WeaponIndex));
}
