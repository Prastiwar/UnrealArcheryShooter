// // Copyright 2018-2019 Tomasz Piowczyk, MIT License

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/PointLightComponent.h"
#include "Lifter.generated.h"

UCLASS()
class CPPLEARN_API ALifter : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALifter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void BeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	UBoxComponent* Box;

	UPROPERTY(EditAnywhere)
		FVector NextLocation;

};
