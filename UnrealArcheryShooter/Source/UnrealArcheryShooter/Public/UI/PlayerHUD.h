// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "UI/ItemGrid.h"
#include "UI/WeaponItem.h"
#include "CoreGame/UASCharacter.h"
#include "Data/UIWeaponData.h"
#include "PlayerHUD.generated.h"

UCLASS()
class UNREALARCHERYSHOOTER_API UPlayerHUD : public UItemGrid
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
		virtual void FillGrid() override;

	UFUNCTION(BlueprintCallable)
		void RefreshScore(float Score);

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* ScoreText;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UDataTable* WeaponsTable;

	UFUNCTION(BlueprintCallable)
		void SetGrid(TArray<UWeaponItem*> WeaponItems);

};
