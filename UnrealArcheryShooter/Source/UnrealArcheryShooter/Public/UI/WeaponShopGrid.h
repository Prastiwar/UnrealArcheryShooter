// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "UI/ItemGrid.h"
#include "Shop/WeaponShop.h"
#include "UI/WeaponShopItem.h"
#include "UnrealArcheryShooterGameMode.h"
#include "WeaponShopGrid.generated.h"

UCLASS()
class UNREALARCHERYSHOOTER_API UWeaponShopGrid : public UItemGrid
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TSubclassOf<class AWeaponShop> WeaponShop;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* ExitButton;

	UFUNCTION(BlueprintCallable)
		void ExitShop();

	UFUNCTION(BlueprintCallable)
		virtual void FillGrid() override;

protected:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
		void SetGrid(const TArray<UWeaponShopItem*>& WeaponItems);

private:
	UFUNCTION()
		void TryExitShop(const bool bBought);

};
