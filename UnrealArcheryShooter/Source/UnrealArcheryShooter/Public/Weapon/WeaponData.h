// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "Weapon/FireBehavior.h"
#include "CooldownData.h"
#include "WeaponData.generated.h"

USTRUCT(BlueprintType)
struct UNREALARCHERYSHOOTER_API FWeaponData
{
	GENERATED_BODY()

public:
	FWeaponData() {}
	~FWeaponData() {}

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USkeletalMesh* WeaponMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FCooldownData FireCooldown;

	UPROPERTY(EditAnywhere)
		UFireBehavior* FireBehavior;

	void Initialize()
	{
		verifyf(FireBehaviorClass != nullptr, TEXT("You forgot to add FireBehaviorClass to WeaponData %s"), *Name.ToString());
		FireBehavior = FireBehaviorClass->GetDefaultObject<UFireBehavior>();
	}

	FORCEINLINE bool operator==(const FWeaponData &Other) const { return Name == Other.Name; }
	FORCEINLINE bool operator!=(const FWeaponData &Other) const { return !(Name == Other.Name); }

	friend uint32 GetTypeHash(const FWeaponData& Other)
	{
		return GetTypeHash(Other.Name)
			+ GetTypeHash(Other.FireBehavior)
			+ GetTypeHash(Other.WeaponMesh)
			+ GetTypeHash(Other.FireCooldown);
	}

private:
	UPROPERTY(EditAnywhere)
		TSubclassOf<UFireBehavior> FireBehaviorClass;

};
