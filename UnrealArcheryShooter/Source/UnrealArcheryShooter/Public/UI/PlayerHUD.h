// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "UI/ItemGrid.h"
#include "UI/WeaponItem.h"
#include "UMG/Public/Components/TextBlock.h"
#include "PlayerHUD.generated.h"

UCLASS()
class UNREALARCHERYSHOOTER_API UPlayerHUD : public UItemGrid
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
		virtual void FillGrid() override;

	UFUNCTION(BlueprintCallable)
		void RefreshScore(const float Score);

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* ScoreText;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class UDataTable* WeaponsTable;

	UFUNCTION(BlueprintCallable)
		void SetGrid(TArray<class UWeaponItem*>& WeaponItems);

};
