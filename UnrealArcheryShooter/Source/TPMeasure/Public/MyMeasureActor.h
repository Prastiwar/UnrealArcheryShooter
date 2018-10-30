// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/

#pragma once

#include "MeasureActor.h"
#include "MyMeasureActor.generated.h"

UCLASS()
class TPMEASURE_API AMyMeasureActor : public AMeasureActor
{
	GENERATED_BODY()

public:
	AMyMeasureActor() {}

protected:
	void BeginPlay() override { RunTests(); }

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
