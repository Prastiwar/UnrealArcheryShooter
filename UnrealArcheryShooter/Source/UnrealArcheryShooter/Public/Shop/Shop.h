// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "TriggerActor.h"
#include "UASCharacter.h"
#include "UnrealArcheryShooterGameMode.h"
#include "Shop.generated.h"

UCLASS()
class UNREALARCHERYSHOOTER_API AShop : public ATriggerActor
{
	GENERATED_BODY()

public:
	AShop();

protected:
	AUnrealArcheryShooterGameMode* GameMode;

	UPROPERTY(EditAnywhere)
		UBoxComponent* BoxTrigger;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> ShopHud;

	virtual void BeginPlay() override;
	virtual void BeginTrigger(AActor* OtherActor) override;
	virtual void EndTrigger(AActor* OtherActor) override;

};
