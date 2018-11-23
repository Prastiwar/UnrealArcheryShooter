// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "Weapon/FireBehavior.h"
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
		struct FCooldownData FireCooldown;

	UPROPERTY(EditAnywhere)
		UFireBehavior* FireBehavior;

	void Initialize()
	{
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
