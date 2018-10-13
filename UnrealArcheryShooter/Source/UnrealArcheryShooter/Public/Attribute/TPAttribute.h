// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "CoreMinimal.h"
#include "TPModifier.h"
#include "TPAttribute.generated.h"

UCLASS(Blueprintable, BlueprintType)
class UNREALARCHERYSHOOTER_API UTPAttribute : public UObject
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FValueChanged, float, Value);

public:
	UPROPERTY(BlueprintAssignable)
		FValueChanged OnChanged;

	UFUNCTION(BlueprintCallable)
		FORCEINLINE float GetValue() const { return Value; }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE float GetBaseValue() const { return BaseValue; }

	UFUNCTION(BlueprintCallable)
		void SetBaseValue(const float NewValue);

	UFUNCTION(BlueprintCallable)
		virtual void Recalculate();

	UFUNCTION(BlueprintCallable)
		virtual int32 Add(const FTPModifier& Modifier);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FTPModifier> Modifiers;

	UPROPERTY(EditAnywhere)
		float BaseValue;

	float Value;

};
