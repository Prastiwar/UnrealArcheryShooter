// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "Projectile.h"
#include "CooldownData.h"
#include "WeaponData.generated.h"

USTRUCT(BlueprintType)
struct UNREALARCHERYSHOOTER_API FWeaponData
{
	GENERATED_BODY()

public:
	FWeaponData() { }

	~FWeaponData() { }

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TSubclassOf<class AProjectile> Projectile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USkeletalMesh* WeaponMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UAnimMontage* FireAnimation;

	UPROPERTY(EditAnywhere)
		FCooldownData FireCooldown;

	FORCEINLINE bool operator==(const FWeaponData &Other) const { return Name == Other.Name; }
	FORCEINLINE bool operator!=(const FWeaponData &Other) const { return !(Name == Other.Name); }

	friend uint32 GetTypeHash(const FWeaponData& Other)
	{
		return GetTypeHash(Other.Name)
			+ GetTypeHash(Other.Projectile)
			+ GetTypeHash(Other.WeaponMesh)
			+ GetTypeHash(Other.FireAnimation)
			+ GetTypeHash(Other.FireCooldown);
	}

};
