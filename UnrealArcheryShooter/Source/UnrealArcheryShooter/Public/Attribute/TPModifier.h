// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "TPModifier.generated.h"

UENUM(BlueprintType)
enum class EModifierType : uint8
{
	FlatIncrease,
	FlatMultiply,
	Percentage
};

USTRUCT(BlueprintType)
struct UNREALARCHERYSHOOTER_API FTPModifier
{
	GENERATED_BODY()

public:
	FTPModifier() {}
	FTPModifier(EModifierType Type, const float Value, UObject* Source) : FTPModifier(Type, Value, (uint8)Type, Source) {}
	FTPModifier(EModifierType Type, const float Value, const int32 Priority) : FTPModifier(Type, Value, Priority, nullptr) {}
	FTPModifier(EModifierType Type, const float Value) : FTPModifier(Type, Value, (uint8)Type, nullptr) {}
	FTPModifier(EModifierType Type, const float Value, const int32 Priority, UObject* Source)
	{
		this->Priority = Priority;
		this->Value = Value;
		this->Type = Type;
		this->Source = Source;
	}
	~FTPModifier() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UObject* Source;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EModifierType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Priority;

	FORCEINLINE bool operator==(const FTPModifier &Other) const {
		return Value == Other.Value && Type == Other.Type && Priority == Other.Priority && Source == Other.Source;
	}

	FORCEINLINE bool operator<(const FTPModifier &Other) const {
		return Priority < Other.Priority;
	}

};
