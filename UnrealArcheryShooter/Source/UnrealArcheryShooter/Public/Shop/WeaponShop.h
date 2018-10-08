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
		virtual bool BuyItem(const UObject* WorldContextObject, const int32 ItemIndex) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, BlueprintReadOnly)
		USoundBase* SuccessSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, BlueprintReadOnly)
		USoundBase* FailSound;

};
