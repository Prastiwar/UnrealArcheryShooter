// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "UI/ItemGrid.h"
#include "UI/WeaponShopItem.h"
#include "Shop/WeaponShop.h"
#include "WeaponShopGrid.generated.h"

class AUnrealArcheryShooterGameMode;

UCLASS()
class UNREALARCHERYSHOOTER_API UWeaponShopGrid : public UItemGrid
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TSubclassOf<AWeaponShop> WeaponShop;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UButton* ExitButton;

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
