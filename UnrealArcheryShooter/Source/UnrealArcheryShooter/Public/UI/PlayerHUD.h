// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "UI/ItemGrid.h"
#include "UI/WeaponItem.h"
#include "PlayerHUD.generated.h"

UCLASS()
class UNREALARCHERYSHOOTER_API UPlayerHUD : public UItemGrid
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
		void RefreshScore(const float Score);

	UFUNCTION(BlueprintCallable)
		void SetNextSelection();

	UFUNCTION(BlueprintCallable)
		void SetPreviousSelection();

	UFUNCTION(BlueprintCallable)
		void SetSelection(int32 NewSelectIndex);

	UFUNCTION(BlueprintCallable)
		virtual void BuildGrid() override;

	void OnDirty_Implementation() override;

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* ScoreText;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class UDataTable* WeaponsTable;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool bAutoResize;

	TArray<UWeaponItem*> FilledWeaponItems;
	int32 ActualSelectedIndex;

	UFUNCTION(BlueprintCallable)
		void SetGrid(TArray<class UWeaponItem*>& WeaponItems);

};
