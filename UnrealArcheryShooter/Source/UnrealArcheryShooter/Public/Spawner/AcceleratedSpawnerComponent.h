// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "Spawner/SpawnerComponent.h"
#include "AcceleratedSpawnerComponent.generated.h"

UCLASS(ClassGroup = (Spawners), meta = (BlueprintSpawnableComponent))
class UNREALARCHERYSHOOTER_API UAcceleratedSpawnerComponent : public USpawnerComponent
{
	GENERATED_BODY()

public:
	UAcceleratedSpawnerComponent();

	UFUNCTION(BlueprintCallable)
		void ChangeFrequency();

	UFUNCTION(BlueprintCallable)
		void SetTimer();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool bSetFrequencyTimerOnBeginPlay;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float TimeToChangeFrequency;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ChangeFrequencyAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector2D SpawnTimeLimitRange;

	FTimerHandle FrequencyTimerHandle;

	void BeginPlay() override;

};
