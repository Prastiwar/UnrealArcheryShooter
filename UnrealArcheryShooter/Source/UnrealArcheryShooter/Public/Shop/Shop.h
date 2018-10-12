// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "TriggerActor.h"
#include "Components/BoxComponent.h"
#include "UnrealArcheryShooterGameMode.h"
#include "Shop.generated.h"

UCLASS(Abstract)
class UNREALARCHERYSHOOTER_API AShop : public ATriggerActor
{
	GENERATED_BODY()

public:
	AShop();
	//virtual bool BuyItem(int ItemIndex) { unimplemented(); return false; }
	// hack to prevent null GetWorld() bug
	virtual bool BuyItem(const UObject* WorldContextObject, const int32 ItemIndex) { unimplemented(); return false; }

	template<typename T>
	FORCEINLINE TArray<T*> GetItemsArray()
	{
		TArray<T*> Items;
		ItemsTable->GetAllRows<T>(TEXT(""), Items);
		return Items;
	}

protected:
	UPROPERTY(EditAnywhere)
		UBoxComponent* BoxTrigger;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> ShopHud;

	UPROPERTY(EditAnywhere)
		UDataTable* ItemsTable;

	virtual void BeginPlay() override;
	void BeginTrigger(AActor* OtherActor) override;
	void EndTrigger(AActor* OtherActor) override;

	FORCEINLINE AUASCharacter* GetPlayerCharacter() { return PlayerCharacter; }
	FORCEINLINE AUnrealArcheryShooterGameMode* GetGameMode() { return GameMode; }

private:
	AUASCharacter* PlayerCharacter;
	AUnrealArcheryShooterGameMode* GameMode;

};
