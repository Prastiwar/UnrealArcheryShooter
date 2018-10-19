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

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		struct FWeaponData Weapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Cost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* Icon;
};
