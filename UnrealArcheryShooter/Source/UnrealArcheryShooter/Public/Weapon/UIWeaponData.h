// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "Engine/DataTable.h"
#include "UIWeaponData.generated.h"

USTRUCT(BlueprintType)
struct UNREALARCHERYSHOOTER_API FUIWeaponData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FUIWeaponData() {}
	~FUIWeaponData() {}

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		struct FWeaponData Weapon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float Cost;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UTexture2D* Icon;
};
