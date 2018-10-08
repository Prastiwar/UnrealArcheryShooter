// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "FloatingActor.generated.h"

UCLASS()
class UNREALARCHERYSHOOTER_API AFloatingActor : public AActor
{
	GENERATED_BODY()

public:
	AFloatingActor();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float TimeScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector FloatDirection;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UCurveFloat* CurveFloat;

private:
	FVector InitLocation;
	FVector TargetLocation;
	float EvaluateTime;

};
