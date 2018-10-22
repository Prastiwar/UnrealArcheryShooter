// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "Shop/WeaponShop.h"
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
		FORCEINLINE UImage* GetImage() const { return ItemImage; }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE class UButton* GetButton() const { return Button; }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE UTextBlock* GetNameText() const { return ItemName; }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE UTextBlock* GetCostText() const { return ItemCost; }

	UFUNCTION(BlueprintCallable)
		void SetShopItem(UTexture2D* const Icon, const FText& Name, const FText& Cost, const int32 DTWeaponIndex, const TSubclassOf<AWeaponShop>& WeaponShop);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UImage* ItemImage;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UButton* Button;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
		UTextBlock* ItemName;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
		UTextBlock* ItemCost;

private:
	int WeaponIndex;
	TSubclassOf<AWeaponShop> WeaponShop;

	UFUNCTION()
		void Buy();

};
