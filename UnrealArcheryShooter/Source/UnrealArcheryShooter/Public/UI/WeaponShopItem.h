// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "UI/WeaponItem.h"
#include "Shop/WeaponShop.h"
#include "UMG/Public/Components/Button.h"
#include "WeaponShopItem.generated.h"

UCLASS()
class UNREALARCHERYSHOOTER_API UWeaponShopItem : public UUserWidget
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBuyButtonClicked, bool, bBought);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UImage* ItemImage;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
		UButton* Button;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
		UTextBlock* ItemName;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
		UTextBlock* ItemCost;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
		FBuyButtonClicked OnBuy;

	UFUNCTION(BlueprintCallable)
		void SetShopItem(UTexture2D* Icon, FText Name, FText Cost);

	UFUNCTION(BlueprintCallable)
		void SetButton(int WeaponIndex, TSubclassOf<class AWeaponShop> WeaponShop);

private:
	int WeaponIndex;
	TSubclassOf<class AWeaponShop> WeaponShop;

	UFUNCTION()
		void ButtonClick();

};
