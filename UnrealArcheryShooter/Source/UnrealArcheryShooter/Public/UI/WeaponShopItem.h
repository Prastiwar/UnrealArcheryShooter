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
	UPROPERTY(EditAnywhere, meta = (BindWidget))
		FBuyButtonClicked OnBuy;

	UFUNCTION(BlueprintCallable)
		FORCEINLINE UImage* GetImage() { return ItemImage; }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE UButton* GetButton() { return Button; }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE UTextBlock* GetNameText() { return ItemName; }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE UTextBlock* GetCostText() { return ItemCost; }

	UFUNCTION(BlueprintCallable)
		void SetShopItem(UTexture2D* const Icon, const FText& Name, const FText& Cost, const int32 DTWeaponIndex, const TSubclassOf<class AWeaponShop>& WeaponShop);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UImage* ItemImage;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
		UButton* Button;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
		UTextBlock* ItemName;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
		UTextBlock* ItemCost;

private:
	int WeaponIndex;
	TSubclassOf<class AWeaponShop> WeaponShop;

	UFUNCTION()
		void Buy();

};
