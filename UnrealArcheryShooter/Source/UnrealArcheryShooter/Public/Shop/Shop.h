// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "TriggerActor.h"
#include "UASCharacter.h"
#include "UnrealArcheryShooterGameMode.h"
#include "Shop.generated.h"

UCLASS(Abstract)
class UNREALARCHERYSHOOTER_API AShop : public ATriggerActor
{
	GENERATED_BODY()

public:
	AShop();

	virtual bool BuyItem(int Index) { unimplemented(); return false; }

protected:
	UPROPERTY(EditAnywhere)
		UBoxComponent* BoxTrigger;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> ShopHud;

	UPROPERTY(EditAnywhere)
		UDataTable* ItemsTable;

	template<typename T>
	TArray<T*> GetItemsArray()
	{
		TArray<T*> Items;
		ItemsTable->GetAllRows<T>(TEXT(""), Items);
		return Items;
	}
	AUASCharacter* GetPlayerCharacter() { return PlayerCharacter; }
	AUnrealArcheryShooterGameMode* GetGameMode() { return GameMode; }

	virtual void BuildShop() {}

	virtual void BeginPlay() override;
	void BeginTrigger(AActor* OtherActor) override;
	void EndTrigger(AActor* OtherActor) override;

private:
	AUASCharacter* PlayerCharacter;
	AUnrealArcheryShooterGameMode* GameMode;

};
