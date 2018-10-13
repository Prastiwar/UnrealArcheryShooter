// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "CoreMinimal.h"
#include "GenericPlatformMath.h"

struct UNREALARCHERYSHOOTER_API FTPMath : public FGenericPlatformMath
{
	/** Loops value from 0 to MaxValue */
	static FORCEINLINE double Repeat(const double& Value, const double& MaxValue)
	{
		const double RepeatValue = Value - FMath::FloorToDouble(Value / MaxValue) * MaxValue;
		return FMath::Clamp(RepeatValue, 0.0, MaxValue);
	}

	/** Loops value from 0 to MaxValue */
	static FORCEINLINE float Repeat(const float& Value, const float& MaxValue)
	{
		const float RepeatValue = Value - FMath::FloorToFloat(Value / MaxValue) * MaxValue;
		return FMath::Clamp(RepeatValue, 0.0f, MaxValue);
	}

	/** Loops value from 0 to MaxValue */
	static FORCEINLINE int Repeat(const int& Value, const int& MaxValue)
	{
		const int RepeatValue = Value - FMath::FloorToInt(Value / MaxValue) * MaxValue;
		return FMath::Clamp(RepeatValue, 0, MaxValue);
	}


	/** Ping pongs value from 0 to MaxValue */
	static FORCEINLINE double PingPong(const double& Value, const double& MaxValue)
	{
		const double RepeatValue = Repeat(Value, MaxValue * 2.0);
		return MaxValue - FMath::Abs(RepeatValue - MaxValue);
	}

	/** Ping pongs value from 0 to MaxValue */
	static FORCEINLINE float PingPong(const float& Value, const float& MaxValue)
	{
		const float RepeatValue = Repeat(Value, MaxValue * 2);
		return MaxValue - FMath::Abs(RepeatValue - MaxValue);
	}

	/** Ping pongs value from 0 to MaxValue */
	static FORCEINLINE int PingPong(const int& Value, const int& MaxValue)
	{
		const int RepeatValue = Repeat(Value, MaxValue * 2);
		return MaxValue - FMath::Abs(RepeatValue - MaxValue);
	}
};
