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
		//virtual bool BuyItem(int ItemIndex) override;
		virtual bool BuyItem(const UObject* WorldContextObject, int ItemIndex) override; // hack to prevent null GetWorld() bug

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		USoundBase* SuccessSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		USoundBase* FailSound;

};
