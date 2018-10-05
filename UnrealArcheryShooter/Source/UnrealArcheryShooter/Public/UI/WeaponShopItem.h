// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "UI/WeaponItem.h"
#include "WeaponShopItem.generated.h"

UCLASS()
class UNREALARCHERYSHOOTER_API UWeaponShopItem : public UWeaponItem
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
		UTextBlock* ItemName;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
		UTextBlock* ItemCost;

	UFUNCTION(BlueprintCallable)
		void SetShopItem(UTexture2D* Icon, FText Name, FText Cost);

};
