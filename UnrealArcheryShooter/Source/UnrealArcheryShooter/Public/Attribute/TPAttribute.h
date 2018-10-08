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
	UTPAttribute();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FTPModifier> Modifiers;

	UPROPERTY(BlueprintAssignable)
		FValueChanged OnChanged;

	UFUNCTION(BlueprintCallable)
		float GetValue();

	UFUNCTION(BlueprintCallable)
		float GetBaseValue();

	UFUNCTION(BlueprintCallable)
		void SetBaseValue(float NewValue);

	UFUNCTION(BlueprintCallable)
		virtual void Recalculate();

protected:
	UPROPERTY(EditAnywhere)
		float BaseValue;

	float Value;

};
