// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "Components/SceneComponent.h"
#include "Weapon/WeaponData.h"
#include "WeaponComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UNREALARCHERYSHOOTER_API UWeaponComponent : public USceneComponent
{
	GENERATED_BODY()
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWeaponChanged);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFire, AProjectile* const, Projectile);

public:
	UWeaponComponent();

	UPROPERTY(BlueprintAssignable)
		FOnFire OnFire;

	UPROPERTY(BlueprintAssignable)
		FWeaponChanged OnWeaponChanged;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FVector MeshFreeZoomPosition;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FVector MeshZoomInPosition;

	UPROPERTY(EditAnywhere, Category = Mesh)
		class USkeletalMeshComponent* FPMeshViewer;

	UPROPERTY(EditAnywhere, Category = Mesh)
		class USkeletalMeshComponent* GunMesh;

	UPROPERTY(EditAnywhere, Category = Mesh)
		class UAnimInstance* AnimInstance;

	UFUNCTION(BlueprintCallable)
		TArray<FWeaponData> GetWeapons() const { return Weapons; }

	TArray<FWeaponData>* GetWeaponsPtr() { return &Weapons; }

	UFUNCTION(BlueprintCallable)
		bool AddWeapon(FWeaponData& Weapon);

	UFUNCTION(BlueprintCallable)
		bool HasWeapon(const FWeaponData& Weapon) const;

	UFUNCTION(BlueprintCallable)
		void SetWeapons(const TArray<FWeaponData> OtherWeapons);

	UFUNCTION(BlueprintCallable)
		void SetWeapon(const int Index);

	UFUNCTION(BlueprintCallable)
		void SwitchToNextWeapon();

	UFUNCTION(BlueprintCallable)
		void SwitchToPreviousWeapon();

	UFUNCTION(BlueprintCallable)
		FORCEINLINE int GetCurrentWeaponIndex() const { return CurrentWeaponIndex; }

	void Fire();
	void PlayFireAnim();
	void ToggleZoom();
	void Zoom(const bool bToZoom);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 CurrentWeaponIndex;

	UPROPERTY(EditAnywhere)
		TArray<FWeaponData> Weapons;

	UPROPERTY(BlueprintReadOnly)
		class UCooldown* Cooldown;

	bool bIsZoomed;

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

};
