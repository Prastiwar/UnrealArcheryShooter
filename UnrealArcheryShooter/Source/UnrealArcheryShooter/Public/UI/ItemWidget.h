// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UMG/Public/Components/Image.h"
#include "UMG/Public/Components/TextBlock.h"
#include "ItemWidget.generated.h"

UCLASS()
class UNREALARCHERYSHOOTER_API UItemWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
		UImage* ItemImage;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
		UTextBlock* ItemName;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
		UTextBlock* ItemCost;

	UFUNCTION(BlueprintCallable)
		void SetItem(UTexture2D* Icon, FText Name, FText Cost);

};
