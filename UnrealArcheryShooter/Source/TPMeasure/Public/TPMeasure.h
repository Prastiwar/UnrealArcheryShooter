// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/

#pragma once

#include "TPMeasureResult.h"

struct TPMEASURE_API FTPMeasure
{

public:
	static FORCEINLINE FTPMeasureResult Measure(FString Label, TFunction<void()> Func)
	{
		double StartTime = StartAndGetTime();
		Func();
		return Stop(StartTime, Label);
	}

	static FORCEINLINE FTPMeasureResult MeasureRepeat(int64 RepeatFunc, FString ResultMessage, TFunction<void()> Func)
	{
		return Measure(ResultMessage, [&]() {
			for (int64 i = 0; i < RepeatFunc; i++)
			{
				Func();
			}
		});
	}

	// Repeat measurement and calculate average results
	static FORCEINLINE FTPMeasureResult MeasureAverage(int64 RepeatToAverage, FString ResultMessage, TFunction<void()> Func)
	{
		double Total = 0;
		for (int64 i = 0; i < RepeatToAverage; i++)
		{
			double StartTime = StartAndGetTime();
			Func();
			Total += Stop(StartTime).GetResultTime();
		}
		return FTPMeasureResult(ResultMessage, Total / RepeatToAverage);
	}

	// Repeat MeasureAverage(..)
	static FORCEINLINE FTPMeasureResult MeasureAverageRepeat(int64 RepeatToAverage, int64 RepeatFunc, FString ResultMessage, TFunction<void()> Func)
	{
		return MeasureAverage(RepeatToAverage, ResultMessage, [&]() {
			for (int64 i = 0; i < RepeatFunc; i++)
			{
				Func();
			}
		});
	}

	// Get StartTime
	static FORCEINLINE double StartAndGetTime()
	{
		return FPlatformTime::Seconds();
	}

	// Returns Result of measuring time of executed code
	static FORCEINLINE FTPMeasureResult Stop(double StartTime, FString ResultMessage = FString())
	{
		return FTPMeasureResult(ResultMessage, FPlatformTime::Seconds() - StartTime);
	}
};
