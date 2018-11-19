// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "Engine/StaticMeshActor.h"
#include "FloatingActor.generated.h"

UCLASS()
class UNREALARCHERYSHOOTER_API AFloatingActor : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	AFloatingActor();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float TimeScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector DirectionOffset;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class UCurveFloat* CurveFloat;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class UCurveFloat* BackCurveFloat;

	UFUNCTION(BlueprintCallable)
		float GetCurveFloatValue(float InTime);

	UFUNCTION(BlueprintCallable)
		FORCEINLINE float GetPosition(float InTime) { return Position; }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE float IsReversed(float InTime) { return bIsReversed; }

	virtual void Interp(float Value);

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	FVector InitLocation;
	FVector TargetLocation;
	float Position;
	bool bIsReversed;
};
