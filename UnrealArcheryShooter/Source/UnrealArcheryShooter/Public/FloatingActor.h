// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "FloatingActor.generated.h"

UCLASS()
class UNREALARCHERYSHOOTER_API AFloatingActor : public AActor
{
	GENERATED_BODY()

public:
	AFloatingActor();

private:
	FVector InitLocation;
	FVector TargetLocation;
	float EvaluateTime;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	
	UPROPERTY(VisibleAnywhere, Category = "Floating")
		UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, Category = "Floating")
		float TimeScale;

	UPROPERTY(EditAnywhere, Category = "Floating")
		FVector FloatDirection;

	UPROPERTY(EditAnywhere, Category = "Floating")
		UCurveFloat* CurveFloat;

};
