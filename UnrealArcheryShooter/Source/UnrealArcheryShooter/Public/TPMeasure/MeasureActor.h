// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "GameFramework/Actor.h"
#include "TPMeasure/TPMeasure.h"
#include "MeasureActor.generated.h"

UCLASS(Abstract)
class UNREALARCHERYSHOOTER_API AMeasureActor : public AActor
{
	GENERATED_BODY()

public:
	AMeasureActor() {}

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 RepeatLength = 1000;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 RepeatAverageLength = 10;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FName ProfileUpdateSampleName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<FString> MeasureNames;

	void Void() {}
	virtual void RunTest()
	{
		MeasureAverageRepeat();
	}

protected:
	virtual void UpdateProfile() { }

	// Iterate over GetMeasureActions() and shows their results with FTPMeasure::MeasureAverageRepeat(RepeatAverageLength, RepeatLength, MeasureNames[i])
	void MeasureAverageRepeat()
	{
		int32 Length = 0;
		TArray<TFunction<void()>> Actions = GetMeasureActionsSafe(Length);
		for (int32 i = 0; i < Length; i++)
		{
			FTPMeasure::MeasureAverageRepeat(RepeatAverageLength, RepeatLength, MeasureNames[i], Actions[i]).ShowLog();
		}
	}

	// Iterate over GetMeasureActions() and shows their results with FTPMeasure::MeasureAverage(MeasureNames[i])
	void MeasureAverage()
	{
		int32 Length = 0;
		TArray<TFunction<void()>> Actions = GetMeasureActionsSafe(Length);
		for (int32 i = 0; i < Length; i++)
		{
			FTPMeasure::MeasureAverage(RepeatLength, MeasureNames[i], Actions[i]).ShowLog();
		}
	}

	// Iterate over GetMeasureActions() and shows their results with FTPMeasure::Measure(MeasureNames[i])
	void Measure()
	{
		int32 Length = 0;
		TArray<TFunction<void()>> Actions = GetMeasureActionsSafe(Length);
		for (int32 i = 0; i < Length; i++)
		{
			FTPMeasure::Measure(MeasureNames[i], Actions[i]).ShowLog();
		}
	}

	// Iterate over GetMeasureActions() and shows their results with FTPMeasure::MeasureRepeat(RepeatLength, MeasureNames[i])
	void MeasureRepeat()
	{
		int32 Length = 0;
		TArray<TFunction<void()>> Actions = GetMeasureActionsSafe(Length);
		for (int32 i = 0; i < Length; i++)
		{
			FTPMeasure::MeasureRepeat(RepeatLength, MeasureNames[i], Actions[i]).ShowLog();
		}
	}

	// Spawns and returns array of ActorClass
	FORCEINLINE TArray<AActor*> SpawnActors(int32 Count, AActor* ActorClass)
	{
		TArray<AActor*> SpawnedActors = TArray<AActor*>();
		SpawnedActors.Reserve(Count);
		if (const UWorld* World = GetWorld())
		{
			for (int32 i = 0; i < Count; i++)
			{
				//AActor* SpawnedActor = World->SpawnActor(ActorClass);
			}
		}
		return SpawnedActors;
	}

	virtual TArray<TFunction<void()>> GetActionsToMeasure() { unimplemented(); return TArray<TFunction<void()>>(); }


private:
	FORCEINLINE TArray<TFunction<void()>> GetMeasureActionsSafe(int32& Length)
	{
		TArray<TFunction<void()>> MeasureActions = GetActionsToMeasure();
		if (MeasureActions.Num() > MeasureNames.Num())
		{
			UE_LOG(LogTemp, Warning, TEXT("Measure names count doesn't match measures count! Creating empty labels..."));
			while (MeasureActions.Num() > MeasureNames.Num())
			{
				MeasureNames.Add(TEXT(""));
			}
		}
		Length = MeasureActions.Num();
		return MeasureActions;
	}

};
