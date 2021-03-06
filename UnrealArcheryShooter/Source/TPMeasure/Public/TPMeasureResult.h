// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/

#pragma once

struct TPMEASURE_API FTPMeasureResult
{

public:
	FTPMeasureResult(FString Label, double ResultTime)
	{
		this->ResultTime = ResultTime;
		this->ResultLabel = FormatResults(Label, ResultTime);
	}
	~FTPMeasureResult() {}

	FORCEINLINE void ShowLog() const
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *ResultLabel);
	}

	FORCEINLINE double GetResultTime() const
	{
		return ResultTime;
	}

	static FORCEINLINE FString FormatResults(FString Label, double ResultTime)
	{
		return Label + " " + FString::SanitizeFloat(ResultTime * 1000, 4) + " ms";
	}

private:
	FString ResultLabel;
	double ResultTime;
};
