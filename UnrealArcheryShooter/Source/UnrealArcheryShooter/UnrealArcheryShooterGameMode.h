// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UnrealArcheryShooterGameMode.generated.h"

UCLASS()
class UNREALARCHERYSHOOTER_API AUnrealArcheryShooterGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AUnrealArcheryShooterGameMode();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player")
		TSubclassOf<class UUserWidget> PlayerHUD;

	UPROPERTY(BlueprintReadWrite)
		UUserWidget* CurrentWidget;
};
