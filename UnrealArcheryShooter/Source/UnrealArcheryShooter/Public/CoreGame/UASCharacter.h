// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "GameFramework/Character.h"
#include "CoreGame/PlayerData.h"
#include "Weapon/WeaponData.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FVector FPMeshFreePosition;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FVector FPMeshZoomPosition;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USkeletalMeshComponent* FirstPersonMeshViewed;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USkeletalMeshComponent* GunMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FirstPersonCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Gameplay)
		USceneComponent* MuzzleLocation;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UFUNCTION(BlueprintCallable)
		FORCEINLINE float GetBaseTurnRate() const { return BaseTurnRate; }

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UFUNCTION(BlueprintCallable)
		FORCEINLINE float GetBaseLookUpRate() const { return BaseLookUpRate; }

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
		TArray<FWeaponData> GetWeapons() const { return Weapons; }
	TArray<FWeaponData>* GetWeaponsPtr() { return &Weapons; }

	UFUNCTION(BlueprintCallable, Category = Weapon)
		bool AddWeapon(FWeaponData& Weapon);

	UFUNCTION(BlueprintCallable, Category = Weapon)
		bool HasWeapon(const FWeaponData& Weapon) const;

	UFUNCTION(BlueprintCallable, Category = Weapon)
		void SetWeapons(const TArray<FWeaponData> OtherWeapons);

	UFUNCTION(BlueprintCallable, Category = Weapon)
		void SetWeapon(const int Index);

	UFUNCTION(BlueprintCallable, Category = Weapon)
		FORCEINLINE int GetCurrentWeaponIndex() const { return CurrentWeaponIndex; }

	UFUNCTION(BlueprintCallable, Category = Weapon)
		void SwitchNextWeapon();

	UFUNCTION(BlueprintCallable, Category = Weapon)
		void SwitchPreviousWeapon();

	// Score Functionality

	UFUNCTION(BlueprintCallable, Category = "Player Score")
		FORCEINLINE float GetScore() const { return PlayerData.Score; }

	UFUNCTION(BlueprintCallable, Category = "Player Score")
		FORCEINLINE float GetScoreMultiplier() const { return ScoreMultiplier; }

	UFUNCTION(BlueprintCallable, Category = "Player Score")
		void AddScore(const float Score);

	UFUNCTION(BlueprintCallable, Category = "Player Score")
		void SetScore(const float Score);

	UFUNCTION(BlueprintCallable, Category = "Player Score")
		void SetScoreMultiplier(const float ScoreMultiplier);

protected:
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;

	UPROPERTY(EditAnywhere, Category = Weapon)
		TArray<FWeaponData> Weapons;

	UPROPERTY(BlueprintReadOnly)
		class UCooldownComponent* CooldownComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UAttributeComponent* AttributeComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Score")
		FPlayerData PlayerData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon)
		int CurrentWeaponIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
		float ScoreMultiplier;

	bool bIsZoomed;

	virtual void BeginPlay();
	virtual void Tick(float DeltaSeconds) override;

	void Fire();
	void Zoom();
	void ZoomImpl(const bool bToZoom);
	void PlayFireAnim();
	void MoveForward(const float Value);
	void MoveSide(const float Value);

	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override; // APawn interface

};
