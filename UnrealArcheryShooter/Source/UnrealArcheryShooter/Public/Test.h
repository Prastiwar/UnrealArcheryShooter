// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/PointLightComponent.h"
#include "DestructibleComponent.h"
#include "Test.generated.h"

UCLASS()
class UNREALARCHERYSHOOTER_API ATest : public AActor
{
	GENERATED_BODY()

public:
	ATest();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	UDestructibleComponent* DestructibleComponent;

	UPROPERTY(EditAnywhere)
	UPointLightComponent* Light;

};
