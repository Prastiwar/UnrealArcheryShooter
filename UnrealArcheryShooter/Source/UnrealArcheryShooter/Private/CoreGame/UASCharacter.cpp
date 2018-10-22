// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "UASCharacter.h"
#include "Projectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Cooldown/CooldownComponent.h"
#include "CoreGame/SaveState.h"

AUASCharacter::AUASCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->RelativeLocation = FVector(-39.56f, 1.75f, 64.f); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	FirstPersonMeshViewed = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	FirstPersonMeshViewed->SetOnlyOwnerSee(true);
	FirstPersonMeshViewed->SetupAttachment(FirstPersonCameraComponent);
	FirstPersonMeshViewed->bCastDynamicShadow = false;
	FirstPersonMeshViewed->CastShadow = false;
	FirstPersonMeshViewed->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);
	FirstPersonMeshViewed->RelativeLocation = FVector(-0.5f, -4.4f, -155.7f);

	// Create a gun mesh component
	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	GunMesh->SetOnlyOwnerSee(true); // only the owning player will see this mesh
	GunMesh->bCastDynamicShadow = false;
	GunMesh->CastShadow = false;
	GunMesh->SetupAttachment(RootComponent);

	MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	MuzzleLocation->SetupAttachment(GunMesh);
	MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));

	AttributeComponent = CreateDefaultSubobject<UAttributeComponent>(TEXT("Attributes"));

	CurrentWeaponIndex = 0;
	ScoreMultiplier = 1.0f;
	PlayerData = FPlayerData();
}

void AUASCharacter::BeginPlay()
{
	Super::BeginPlay();

	//Attach gun mesh component to Skeleton, doing it here because the skeleton is not yet created in the constructor
	GunMesh->AttachToComponent(FirstPersonMeshViewed, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
	FirstPersonMeshViewed->SetHiddenInGame(false, true);
	CooldownComponent = NewObject<UCooldownComponent>();
	ZoomImpl(false);
}

void AUASCharacter::Tick(float DeltaSeconds)
{
	CooldownComponent->Tick(DeltaSeconds);
}

void AUASCharacter::SavePlayer()
{
	USaveState* const SaveInstance = USaveState::Get();
	SaveInstance->SavePlayer(this);
	if (!SaveInstance->Save(SaveInstance))
	{
		UE_LOG(LogTemp, Error, TEXT("Save failed!"))
	}
}

void AUASCharacter::Load()
{
	USaveState* const SaveInstance = USaveState::Load();
	if (SaveInstance)
	{
		SaveInstance->LoadPlayer(this);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Load failed!"))
	}
}

void AUASCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind weapon change events
	PlayerInputComponent->BindAction("WheelUp", IE_Pressed, this, &AUASCharacter::SwitchNextWeapon);
	PlayerInputComponent->BindAction("WheelDown", IE_Pressed, this, &AUASCharacter::SwitchPreviousWeapon);
	PlayerInputComponent->BindAction("E", IE_Pressed, this, &AUASCharacter::SwitchNextWeapon);
	PlayerInputComponent->BindAction("Q", IE_Pressed, this, &AUASCharacter::SwitchPreviousWeapon);

	// Bind fire events
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AUASCharacter::Fire);
	PlayerInputComponent->BindAction("Zoom", IE_Pressed, this, &AUASCharacter::Zoom);

	// Bind Persistence
	PlayerInputComponent->BindAction("SaveGame", IE_Pressed, this, &AUASCharacter::SavePlayer);
	PlayerInputComponent->BindAction("LoadGame", IE_Pressed, this, &AUASCharacter::Load);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &AUASCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveSide", this, &AUASCharacter::MoveSide);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
}

void AUASCharacter::Fire()
{
	if (Weapons.IsValidIndex(CurrentWeaponIndex))
	{
		if (Weapons[CurrentWeaponIndex].FireCooldown.bIsCompleted)
		{
			UWorld* const World = GetWorld();
			if (World != NULL)
			{
				FActorSpawnParameters SpawnParams;
				SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

				AProjectile* const Projectile = World->SpawnActor<AProjectile>(
					Weapons[CurrentWeaponIndex].Projectile, MuzzleLocation->GetComponentLocation(), GetControlRotation(), SpawnParams);
				if (Projectile)
				{
					AddScore(-Projectile->GetFireCost());
					CooldownComponent->SetCooldown(&Weapons[CurrentWeaponIndex].FireCooldown);
				}
			}
			PlayFireAnim();
		}
	}
}

void AUASCharacter::PlayFireAnim()
{
	if (Weapons[CurrentWeaponIndex].FireAnimation != NULL)
	{
		UAnimInstance* const AnimInstance = FirstPersonMeshViewed->GetAnimInstance();
		if (AnimInstance != NULL)
		{
			AnimInstance->Montage_Play(Weapons[CurrentWeaponIndex].FireAnimation, 1.f);
		}
	}
}

void AUASCharacter::Zoom()
{
	bIsZoomed = !bIsZoomed;
	ZoomImpl(bIsZoomed);
}

void AUASCharacter::ZoomImpl(const bool bToZoom)
{
	if (bToZoom)
	{
		FirstPersonMeshViewed->SetRelativeLocation(FPMeshZoomPosition);
	}
	else
	{
		FirstPersonMeshViewed->SetRelativeLocation(FPMeshFreePosition);
	}
}

void AUASCharacter::MoveForward(const float Value)
{
	if (Value != 0.0f)
	{
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AUASCharacter::MoveSide(const float Value)
{
	if (Value != 0.0f)
	{
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AUASCharacter::AddScore(const float Score)
{
	PlayerData.Score += Score * GetScoreMultiplier();
	if (PlayerData.Score < 0.0f)
	{
		PlayerData.Score = 0.0f;
	}
	OnScoreChanged.Broadcast(PlayerData.Score);
}

void AUASCharacter::SetScore(const float Score)
{
	PlayerData.Score = Score;
}

void AUASCharacter::SetScoreMultiplier(const float ScoreMultiplier)
{
	this->ScoreMultiplier = ScoreMultiplier;
}

bool AUASCharacter::AddWeapon(const FWeaponData& Weapon)
{
	if (!HasWeapon(Weapon))
	{
		Weapons.Add(Weapon);
		return true;
	}
	return false;
}

bool AUASCharacter::HasWeapon(const FWeaponData& Weapon) const
{
	return Weapons.Contains(Weapon);
}

void AUASCharacter::SetWeapons(const TArray<FWeaponData> OtherWeapons)
{
	Weapons = OtherWeapons;
}

void AUASCharacter::SwitchPreviousWeapon()
{
	SetWeapon(CurrentWeaponIndex - 1);
}

void AUASCharacter::SwitchNextWeapon()
{
	SetWeapon(CurrentWeaponIndex + 1);
}

void AUASCharacter::SetWeapon(const int Index)
{
	CurrentWeaponIndex = Index;
	if (CurrentWeaponIndex >= Weapons.Num())
	{
		CurrentWeaponIndex = 0;
	}
	else if (CurrentWeaponIndex < 0)
	{
		CurrentWeaponIndex = Weapons.Num() - 1;
	}
	GunMesh->SetSkeletalMeshWithoutResettingAnimation(Weapons[CurrentWeaponIndex].WeaponMesh);
	OnWeaponChanged.Broadcast();
}
