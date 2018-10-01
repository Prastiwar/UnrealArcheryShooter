// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "WeaponData.h"
#include "Engine/DataTable.h"
#include "UIWeaponData.generated.h"

USTRUCT()
struct UNREALARCHERYSHOOTER_API FUIWeaponData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FUIWeaponData() {}
	~FUIWeaponData() {}

public:
	UPROPERTY(EditAnywhere)
		FWeaponData Weapon;

	UPROPERTY(EditAnywhere)
		float Cost;

	UPROPERTY(EditAnywhere)
		UTexture2D* Icon;
};
