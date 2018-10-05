// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "WeaponShopItem.h"

void UWeaponShopItem::SetShopItem(UTexture2D* Icon, FText Name, FText Cost)
{
	ItemImage->SetBrushFromTexture(Icon);
	ItemName->SetText(Name);
	ItemCost->SetText(Cost);
}

void UWeaponShopItem::SetButton(int Index, TSubclassOf<class AWeaponShop> WeaponShop)
{
	ButtonIndex = Index;
	this->WeaponShop = WeaponShop;
	Button->OnClicked.AddDynamic(this, &UWeaponShopItem::ButtonClick);
}

void UWeaponShopItem::ButtonClick()
{
	OnBuy.Broadcast(WeaponShop->GetDefaultObject<AWeaponShop>()->BuyItem(this, ButtonIndex));
}
