// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Data/PlayerData.h"
#include "Data/WeaponData.h"
#include "CooldownComponent.h"
#include "UASCharacter.generated.h"

UCLASS(config = Game)
class UNREALARCHERYSHOOTER_API AUASCharacter : public ACharacter
{
	GENERATED_BODY()

		DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWeaponChanged);
		DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FScoreChanged, float, Score);

public:
	AUASCharacter();

	UPROPERTY(BlueprintAssignable)
		FWeaponChanged OnWeaponChanged;

	UPROPERTY(BlueprintAssignable)
		FScoreChanged OnScoreChanged;

	static AUASCharacter* GetUASCharacter(const UWorld* World)
	{
		if (World)
		{
			if (World->GetFirstPlayerController())
			{
				return Cast<AUASCharacter>(World->GetFirstPlayerController()->GetCharacter());
			}
		}
		return nullptr;
	}

protected:
	virtual void BeginPlay();
	virtual void Tick(float DeltaSeconds) override;

	void OnFire();
	void PlayFireAnim();
	void MoveForward(float Value);
	void MoveSide(float Value);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override; // APawn interface

private:
	UPROPERTY(VisibleAnywhere)
		UCooldownComponent* CooldownComponent;

	UPROPERTY(EditAnywhere, Category = "Player Score")
		FPlayerData PlayerData;

	float ScoreMultiplier;

	UPROPERTY(EditDefaultsOnly, Category = Weapon)
		TArray<FWeaponData> Weapons;

	UPROPERTY(EditDefaultsOnly, Category = Weapon)
		int CurrentWeaponIndex;

public:
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USkeletalMeshComponent* FirstPersonMeshViewed;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USkeletalMeshComponent* GunMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FirstPersonCameraComponent;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		USceneComponent* MuzzleLocation;

	UFUNCTION(BlueprintCallable)
		TArray<FWeaponData> GetWeapons() { return Weapons; }

	void AddWeapon(FWeaponData& Weapon) { Weapons.Add(Weapon); }

	UFUNCTION(BlueprintCallable, Category = "Player Score")
		float GetScore();

	UFUNCTION(BlueprintCallable, Category = "Player Score")
		void AddScore(float Score);

	UFUNCTION(BlueprintCallable, Category = "Player Score")
		float GetScoreMultiplier();

	UFUNCTION(BlueprintCallable, Category = "Player Score")
		void SetScoreMultiplier(float ScoreMultiplier);

	UFUNCTION(BlueprintCallable, Category = Weapon)
		int GetCurrentWeaponIndex() { return CurrentWeaponIndex; }

	UFUNCTION(BlueprintCallable, Category = Weapon)
		void SwitchNextWeapon();

	UFUNCTION(BlueprintCallable, Category = Weapon)
		void SwitchPreviousWeapon();

	UFUNCTION(BlueprintCallable, Category = Weapon)
		void SetWeapon(int Index);

};
