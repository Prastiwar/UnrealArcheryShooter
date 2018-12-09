// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

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
	static FORCEINLINE int32 Repeat(const int32& Value, const int32& MaxValue)
	{
		const int32 RepeatValue = Value - FMath::FloorToint32(Value / MaxValue) * MaxValue;
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
	static FORCEINLINE int32 PingPong(const int32& Value, const int32& MaxValue)
	{
		const int32 RepeatValue = Repeat(Value, MaxValue * 2);
		return MaxValue - FMath::Abs(RepeatValue - MaxValue);
	}

	/** Clamps Value between MinValue and MaxValue and returns true if already reached MinValue or MaxValue */
	static FORCEINLINE bool Clamp(int32& Value, const int32 MinValue, const int32 MaxValue)
	{
		if (Value >= MaxValue)
		{
			Value = MaxValue;
			return true;
		}
		else if (Value <= MinValue)
		{
			Value = MinValue;
			return true;
		}
		return false;
	}

	/** Clamps Value between MinValue and MaxValue and returns true if already reached MinValue or MaxValue */
	static FORCEINLINE bool Clamp(float& Value, const float MinValue, const float MaxValue)
	{
		if (Value >= MaxValue)
		{
			Value = MaxValue;
			return true;
		}
		else if (Value <= MinValue)
		{
			Value = MinValue;
			return true;
		}
		return false;
	}

};
