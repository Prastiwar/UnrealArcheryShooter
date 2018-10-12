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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UImage* ItemImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UProgressBar* CooldownProgress;

	UFUNCTION(BlueprintCallable)
		void SetItem(UTexture2D* Icon, bool bSelected);

	UFUNCTION(BlueprintCallable)
		void SetProgressPercentage(float Percentage);

};
