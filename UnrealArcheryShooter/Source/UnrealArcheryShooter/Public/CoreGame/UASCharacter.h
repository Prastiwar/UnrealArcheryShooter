// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "GameFramework/Character.h"
#include "Data/PlayerData.h"
#include "Data/WeaponData.h"
#include "Attribute/TPAttribute.h"
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

	static FORCEINLINE AUASCharacter* GetUASCharacter(const UWorld* World)
	{
		if (World)
		{
			if (AController* Controller = World->GetFirstPlayerController())
			{
				return Cast<AUASCharacter>(Controller->GetCharacter());
			}
		}
		return nullptr;
	}

	// Persistence Functionality

	UFUNCTION(BlueprintCallable)
		void SavePlayer();

	UFUNCTION(BlueprintCallable)
		void Load();

	// Weapon Functionality

	UFUNCTION(BlueprintCallable, Category = Weapon)
		TArray<FWeaponData> GetWeapons() { return Weapons; }

	UFUNCTION(BlueprintCallable, Category = Weapon)
		bool AddWeapon(FWeaponData& Weapon);

	UFUNCTION(BlueprintCallable, Category = Weapon)
		bool HasWeapon(FWeaponData& Weapon);

	UFUNCTION(BlueprintCallable, Category = Weapon)
		void SetWeapons(TArray<FWeaponData> OtherWeapons);

	UFUNCTION(BlueprintCallable, Category = Weapon)
		void SetWeapon(int Index);

	UFUNCTION(BlueprintCallable, Category = Weapon)
		int GetCurrentWeaponIndex() { return CurrentWeaponIndex; }

	UFUNCTION(BlueprintCallable, Category = Weapon)
		void SwitchNextWeapon();

	UFUNCTION(BlueprintCallable, Category = Weapon)
		void SwitchPreviousWeapon();

	// Score Functionality

	UFUNCTION(BlueprintCallable, Category = "Player Score")
		float GetScore();

	UFUNCTION(BlueprintCallable, Category = "Player Score")
		void AddScore(float Score);

	UFUNCTION(BlueprintCallable, Category = "Player Score")
		void SetScore(float Score);

	UFUNCTION(BlueprintCallable, Category = "Player Score")
		float GetScoreMultiplier();

	UFUNCTION(BlueprintCallable, Category = "Player Score")
		void SetScoreMultiplier(float ScoreMultiplier);

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

	UPROPERTY()
		UCooldownComponent* CooldownComponent;

	//UPROPERTY()
		//UAttributeComponent* AttributeComponent;

	UPROPERTY(EditAnywhere, Category = Weapon)
		TArray<FWeaponData> Weapons;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Score")
		FPlayerData PlayerData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon)
		int CurrentWeaponIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
		float ScoreMultiplier;

};
