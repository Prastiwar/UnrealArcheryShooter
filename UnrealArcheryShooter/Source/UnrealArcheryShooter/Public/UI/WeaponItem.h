// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UMG/Public/Components/Image.h"
#include "UMG/Public/Components/TextBlock.h"
#include "UMG/Public/Components/ProgressBar.h"
#include "WeaponItem.generated.h"

UCLASS()
class UNREALARCHERYSHOOTER_API UWeaponItem : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
		FORCEINLINE UProgressBar* GetCooldownProgress() { return CooldownProgress; }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE UImage* GetItemImage() { return ItemImage; }

	UFUNCTION(BlueprintCallable)
		void SetItem(UTexture2D* Icon, const bool bSelected);

	UFUNCTION(BlueprintCallable)
		void SetProgressPercentage(const float Percentage);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UImage* ItemImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UProgressBar* CooldownProgress;

};
