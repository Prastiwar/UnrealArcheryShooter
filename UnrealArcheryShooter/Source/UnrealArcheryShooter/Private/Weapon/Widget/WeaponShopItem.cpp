// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "WeaponShopItem.h"
#include "UMG/Public/Components/Button.h"
#include "UMG/Public/Components/TextBlock.h"

void UWeaponShopItem::SetShopItem(UTexture2D* const Icon, const FText& Name, const FText& Cost, const int32 DTWeaponIndex, const TSubclassOf<AWeaponShop>& WeaponShop)
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
