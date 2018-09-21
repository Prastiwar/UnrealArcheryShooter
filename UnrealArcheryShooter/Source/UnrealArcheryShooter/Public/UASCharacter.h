// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Data/PlayerData.h"
#include "Data/WeaponData.h"
#include "UASCharacter.generated.h"

UCLASS(config = Game)
class UNREALARCHERYSHOOTER_API AUASCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AUASCharacter();

protected:
	virtual void BeginPlay();

	void OnFire();
	void MoveForward(float Val);
	void MoveSide(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

protected:
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override; // APawn interface

private:
	UPROPERTY(EditAnywhere, Category = "Player Score")
		FPlayerData PlayerData;

public:
	FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	UFUNCTION(BlueprintCallable, Category = "Player Score")
		void AddScore(float Score);

	UFUNCTION(BlueprintCallable, Category = "Player Score")
		float GetScore();

	UFUNCTION(BlueprintCallable, Category = Weapon)
		void SwitchNextWeapon();

	UFUNCTION(BlueprintCallable, Category = Weapon)
		void SwitchPreviousWeapon();

	UFUNCTION(BlueprintCallable, Category = Weapon)
		void SetWeapon(int Index);

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USkeletalMeshComponent* Mesh1P;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USkeletalMeshComponent* FP_Gun;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USceneComponent* FP_MuzzleLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FirstPersonCameraComponent;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector GunOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class UAnimMontage* FireAnimation;

	UPROPERTY(EditDefaultsOnly, Category = Weapon)
		TArray<FWeaponData> Weapons;

	UPROPERTY(EditDefaultsOnly, Category = Weapon)
		int CurrentWeaponIndex;

};
