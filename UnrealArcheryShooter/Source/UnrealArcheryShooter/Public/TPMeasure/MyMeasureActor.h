// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "TPMeasure/MeasureActor.h"
#include "MyMeasureActor.generated.h"

UCLASS()
class UNREALARCHERYSHOOTER_API AMyMeasureActor : public AMeasureActor
{
	GENERATED_BODY()

public:
	AMyMeasureActor() {}

protected:
	void BeginPlay() override
	{
		RunTest();
	}

	virtual TArray<TFunction<void()>> GetActionsToMeasure()
	{
		TArray<TFunction<void()>> Actions = TArray<TFunction<void()>>();
		Actions.Add([this]() { FirstMeasure(); });
		Actions.Add([this]() { SecondMeasure(); });
		return Actions;
	}

	void FirstMeasure()
	{

	}

	void SecondMeasure()
	{

	}

};
