// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "Game/UASCharacter.h"
#include "Blueprint/UserWidget.h"
#include "Data/UIWeaponData.h"
#include "SButton.h"
#include "PlayerHUDBuilder.generated.h"

UCLASS(Blueprintable)
class UNREALARCHERYSHOOTER_API UPlayerHUDBuilder : public UObject
{
	GENERATED_BODY()

public:
	UPlayerHUDBuilder();
	~UPlayerHUDBuilder();

	TSubclassOf<class UUserWidget> GetPlayerHUD() { return PlayerHUD; }

	UFUNCTION(BlueprintCallable)
		virtual void BuildWeaponSlotsWidget(uint8 Count);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		TSubclassOf<class UUserWidget> PlayerHUD;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UDataTable* WeaponsTable;

};
