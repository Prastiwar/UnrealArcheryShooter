// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "CooldownData.h"
#include "WeaponData.generated.h"

USTRUCT()
struct UNREALARCHERYSHOOTER_API FWeaponData
{
	GENERATED_BODY()

public:
	FWeaponData() { }

	~FWeaponData() { }

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AProjectile> Projectile;

	UPROPERTY(EditAnywhere)
		USkeletalMesh* WeaponMesh;

	UPROPERTY(EditAnywhere)
		class UAnimMontage* FireAnimation;

	UPROPERTY(EditAnywhere)
		FCooldownData FireCooldown;

};
