// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "GameFramework/Actor.h"
#include "Shop.generated.h"

class AUnrealArcheryShooterGameMode;

UCLASS(Abstract)
class UNREALARCHERYSHOOTER_API AShop : public AActor
{
	GENERATED_BODY()

public:
	AShop();
	//virtual bool BuyItem(int32 ItemIndex) { unimplemented(); return false; }
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
		TSubclassOf<class UUserWidget> ShopHud;

	UPROPERTY(EditAnywhere)
		class UDataTable* ItemsTable;

	UPROPERTY(EditAnywhere)
		class UShapeComponent* TriggerShape;

	FORCEINLINE AUASCharacter* GetPlayerCharacter() const { return PlayerCharacter; }
	FORCEINLINE AUnrealArcheryShooterGameMode* GetGameMode() const { return GameMode; }

	virtual void BeginPlay() override;

	void BeginTrigger(AActor* OtherActor, UPrimitiveComponent* OtherComp);
	void EndTrigger(AActor* OtherActor, UPrimitiveComponent* OtherComp);

private:
	AUASCharacter* PlayerCharacter;
	AUnrealArcheryShooterGameMode* GameMode;

};
