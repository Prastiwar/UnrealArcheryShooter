// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "Toggle.generated.h"

USTRUCT(BlueprintType)
struct UNREALARCHERYSHOOTER_API FToggle
{
	GENERATED_BODY()
	DECLARE_DELEGATE_OneParam(FActivation, const bool);

public:
	FActivation OnToggled;

	FORCEINLINE bool IsActive() const { return bIsActive; }

	void Toggle() { SetToggle(!bIsActive); }

	void SetToggle(const bool bActive)
	{
		bIsActive = bActive;
		OnToggled.ExecuteIfBound(bIsActive);
	}

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
		bool bIsActive;

};
