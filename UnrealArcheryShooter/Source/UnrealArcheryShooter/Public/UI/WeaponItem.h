// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "Blueprint/UserWidget.h"
#include "WeaponItem.generated.h"

UCLASS()
class UNREALARCHERYSHOOTER_API UWeaponItem : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
		FORCEINLINE class UProgressBar* GetCooldownProgress() const { return CooldownProgress; }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE class UImage* GetItemImage() const { return ItemImage; }

	UFUNCTION(BlueprintCallable)
		void SetItem(UTexture2D* Icon, const bool bSelected);

	UFUNCTION(BlueprintCallable)
		void SetItemSelection(const bool bSelected);

	UFUNCTION(BlueprintCallable)
		void SetProgressPercentage(const float Percentage);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UImage* ItemImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UProgressBar* CooldownProgress;

};
