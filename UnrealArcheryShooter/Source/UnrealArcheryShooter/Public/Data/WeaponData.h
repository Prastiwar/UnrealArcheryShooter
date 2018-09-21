// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "WeaponData.generated.h"

USTRUCT()
struct UNREALARCHERYSHOOTER_API FWeaponData
{
	GENERATED_BODY()

public:
	FWeaponData();
	~FWeaponData();

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AProjectile> Projectile;

	UPROPERTY(EditAnywhere)
		USkeletalMesh* WeaponMesh;

};