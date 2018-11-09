// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "GameFramework/Character.h"
#include "CoreGame/PlayerData.h"
#include "UASCharacter.generated.h"


UCLASS(config = Game)
class UNREALARCHERYSHOOTER_API AUASCharacter : public ACharacter
{
	GENERATED_BODY()
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FScoreChanged, float, Score);

public:
	AUASCharacter();

	UPROPERTY(BlueprintAssignable)
		FScoreChanged OnScoreChanged;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USkeletalMeshComponent* FirstPersonMeshViewed;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USkeletalMeshComponent* GunMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FirstPersonCameraComponent;

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

	// Score Functionality

	UFUNCTION(BlueprintCallable, Category = "Player Score")
		FORCEINLINE float GetScore() const { return PlayerData.Score; }

	UFUNCTION(BlueprintCallable, Category = "Player Score")
		FORCEINLINE float GetScoreMultiplier() const { return ScoreMultiplier; }

	UFUNCTION(BlueprintCallable, Category = "Player Score")
		FORCEINLINE UWeaponComponent* GetWeaponComponent() const { return WeaponComponent; }

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

	UPROPERTY(EditDefaultsOnly, Category = Weapon)
		class UDataTable* WeaponsTable;

	UPROPERTY(EditDefaultsOnly, Category = Weapon)
		TArray<FName> InitialWeaponsNames;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UAttributeComponent* AttributeComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class UWeaponComponent* WeaponComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Score")
		FPlayerData PlayerData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
		float ScoreMultiplier;

	UFUNCTION(BlueprintCallable)
		void OnFire(AProjectile* const Projectile);

	bool bIsZoomed;

	virtual void BeginPlay();
	virtual void Tick(float DeltaSeconds) override;

	void MoveForward(const float Value);
	void MoveSide(const float Value);

	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override; // APawn interface

};
