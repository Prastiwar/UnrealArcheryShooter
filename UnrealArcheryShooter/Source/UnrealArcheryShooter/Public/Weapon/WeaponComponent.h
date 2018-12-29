// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "Components/SceneComponent.h"
#include "WeaponData.h"
#include "WeaponComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UNREALARCHERYSHOOTER_API UWeaponComponent : public USceneComponent
{
	GENERATED_BODY()
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWeaponChanged);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFire, UFireBehavior* const, FireBehavior);

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

	UFUNCTION(BlueprintCallable)
		TArray<FWeaponData> GetWeapons() const { return Weapons; }

	UFUNCTION(BlueprintCallable)
		TArray<FWeaponData>& GetWeaponsRef() { return Weapons; }

	UFUNCTION(BlueprintCallable)
		bool AddWeapon(FWeaponData& Weapon);

	UFUNCTION(BlueprintCallable)
		bool HasWeapon(const FWeaponData& Weapon) const;

	UFUNCTION(BlueprintCallable)
		void SetWeapons(const TArray<FWeaponData> OtherWeapons);

	UFUNCTION(BlueprintCallable)
		void SetWeaponsByNames(const TArray<FName> WeaponNames);

	UFUNCTION(BlueprintCallable)
		void SetWeapon(const int32 Index);

	UFUNCTION(BlueprintCallable)
		void SwitchToNextWeapon();

	UFUNCTION(BlueprintCallable)
		void SwitchToPreviousWeapon();

	UFUNCTION(BlueprintCallable)
		void Fire();

	UFUNCTION(BlueprintCallable)
		void ToggleZoom();

	UFUNCTION(BlueprintCallable)
		void Zoom(const bool bToZoom);

	UFUNCTION(BlueprintCallable)
		FORCEINLINE int32 GetCurrentWeaponIndex() const { return CurrentWeaponIndex; }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE bool IsZooming() const { return bIsZoomed; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 CurrentWeaponIndex;

	UPROPERTY(VisibleAnywhere)
		TArray<FWeaponData> Weapons;

	UPROPERTY(BlueprintReadOnly)
		class UCooldownComponent* Cooldown;

	UPROPERTY(EditDefaultsOnly)
		class UDataTable* WeaponsTable;

	UPROPERTY(BlueprintReadOnly)
		class UAnimInstance* AnimInstance;

	UPROPERTY(EditDefaultsOnly)
		FComponentReference FPMeshViewerRef;

	UPROPERTY(EditDefaultsOnly)
		FComponentReference CameraRef;

	UPROPERTY(EditDefaultsOnly)
		FComponentReference GunMeshRef;

	UPROPERTY(BlueprintReadOnly)
		class USkeletalMeshComponent* FPMeshViewer;

	UPROPERTY(BlueprintReadOnly)
		class USkeletalMeshComponent* GunMesh;

	UPROPERTY(BlueprintReadOnly)
		class UCameraComponent* Camera;

	virtual void BeginPlay() override;

	void PlayFireAnim();

private:
	bool bIsZoomed;

};
