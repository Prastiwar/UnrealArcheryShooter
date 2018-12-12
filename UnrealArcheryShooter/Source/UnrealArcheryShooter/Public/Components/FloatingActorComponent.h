// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "Components/ActorComponent.h"
#include "FloatingActorComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UNREALARCHERYSHOOTER_API UFloatingActorComponent : public UActorComponent
{
	GENERATED_BODY()
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDirectionChanged, const bool, bIsReversed);

public:
	UFloatingActorComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float TimeScale;

	UFUNCTION(BlueprintCallable)
		void SetTarget(AActor* const NewTarget);

	UFUNCTION(BlueprintCallable)
		float GetCurveFloatValue(float InTime);

	UPROPERTY(BlueprintAssignable)
		FDirectionChanged OnDirectionChanged;

	// Is it playing back now?
	UFUNCTION(BlueprintCallable)
		FORCEINLINE float IsReversed(float InTime) { return bIsReversed; }

	// Returns actual normalized curve value
	UFUNCTION(BlueprintCallable)
		FORCEINLINE float GetActualPosition(float InTime) { return Position; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector DirectionOffset;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class UCurveFloat* CurveFloat;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class UCurveFloat* BackCurveFloat;

	AActor* Target;
	float Position;
	bool bIsReversed;

	virtual void Interp(float Value);

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	FVector InitLocation;
	FVector TargetLocation;

};
