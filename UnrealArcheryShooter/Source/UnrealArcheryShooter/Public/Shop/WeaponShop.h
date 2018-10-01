// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "Shop/Shop.h"
#include "Data/UIWeaponData.h"
#include "WeaponShop.generated.h"

UCLASS()
class UNREALARCHERYSHOOTER_API AWeaponShop : public AShop
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
		virtual bool BuyItem(int Index) override;

protected:
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget*> WeaponItem;

	virtual void BuildShop() override;

};
