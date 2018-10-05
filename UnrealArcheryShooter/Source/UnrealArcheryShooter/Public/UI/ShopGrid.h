// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "CoreMinimal.h"
#include "UI/ItemGrid.h"
#include "UnrealArcheryShooterGameMode.h"
#include "ShopGrid.generated.h"

UCLASS()
class UNREALARCHERYSHOOTER_API UShopGrid : public UItemGrid
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* ExitButton;

	UFUNCTION(BlueprintCallable)
		void ExitShop();

protected:
	virtual void NativeConstruct() override;

};
