// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "CoreMinimal.h"
#include "TPModifier.generated.h"

UENUM(BlueprintType)
enum class ModifierType : uint8
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
	FTPModifier(ModifierType Type, float Value, UObject* Source) : FTPModifier(Type, Value, (uint8)Type, Source) { }
	FTPModifier(ModifierType Type, float Value, int Priority) : FTPModifier(Type, Value, Priority, nullptr) { }
	FTPModifier(ModifierType Type, float Value) : FTPModifier(Type, Value, (uint8)Type, nullptr) { }
	FTPModifier(ModifierType Type, float Value, int Priority, UObject* Source)
	{
		this->Priority = Priority;
		this->Value = Value;
		this->Type = Type;
		this->Source = Source;
	}
	~FTPModifier() {}

	UPROPERTY(EditAnywhere)
		UObject* Source;

	UPROPERTY(EditAnywhere)
		float Value;

	UPROPERTY(EditAnywhere)
		ModifierType Type;

	UPROPERTY(EditAnywhere)
		int Priority;

	FORCEINLINE bool operator==(const FTPModifier &Other) const {
		return Value == Other.Value && Type == Other.Type && Priority == Other.Priority && Source == Other.Source;
	}

	FORCEINLINE bool operator<(const FTPModifier &Other) const {
		return Priority < Other.Priority;
	}

};
