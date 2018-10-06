// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "UASCharacter.h"
#include "Projectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

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
	GunMesh->SetOnlyOwnerSee(true);			// only the owning player will see this mesh
	GunMesh->bCastDynamicShadow = false;
	GunMesh->CastShadow = false;
	GunMesh->SetupAttachment(RootComponent);

	MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	MuzzleLocation->SetupAttachment(GunMesh);
	MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));

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
}

void AUASCharacter::Tick(float DeltaSeconds)
{
	//CooldownComponent->Tick();
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

	// Bind fire event
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AUASCharacter::OnFire);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &AUASCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveSide", this, &AUASCharacter::MoveSide);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AUASCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
}

void AUASCharacter::OnFire()
{
	if (Weapons.IsValidIndex(CurrentWeaponIndex))
	{
		//GLog->Log(Weapons[CurrentWeaponIndex].FireCooldownPtr->IsCompleted ? TEXT("true") : TEXT("false"));
		//GLog->Log(FString::SanitizeFloat(Weapons[CurrentWeaponIndex].FireCooldownPtr->CooldownTime));
		//if (Weapons[CurrentWeaponIndex].FireCooldownPtr->IsCompleted)
		//{
		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			AProjectile* Projectile = World->SpawnActor<AProjectile>(
				Weapons[CurrentWeaponIndex].Projectile, MuzzleLocation->GetComponentLocation(), GetControlRotation(), SpawnParams);
			if (Projectile)
			{
				AddScore(-Projectile->GetFireCost());
				//if (CooldownComponent)
				//{
					//Weapons[CurrentWeaponIndex].FireCooldown = CooldownComponent->SetCooldown(Weapons[CurrentWeaponIndex].FireCooldown);
					//Weapons[CurrentWeaponIndex].FireCooldownPtr = &Weapons[CurrentWeaponIndex].FireCooldown;
				//}
			}
		}
		PlayFireAnim();
		//}
	}
}

void AUASCharacter::PlayFireAnim()
{
	if (Weapons[CurrentWeaponIndex].FireAnimation != NULL)
	{
		UAnimInstance* AnimInstance = FirstPersonMeshViewed->GetAnimInstance();
		if (AnimInstance != NULL)
		{
			AnimInstance->Montage_Play(Weapons[CurrentWeaponIndex].FireAnimation, 1.f);
		}
	}
}

void AUASCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AUASCharacter::MoveSide(float Value)
{
	if (Value != 0.0f)
	{
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AUASCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AUASCharacter::AddScore(float Score)
{
	PlayerData.Score += Score * GetScoreMultiplier();
	if (PlayerData.Score < 0.0f)
	{
		PlayerData.Score = 0.0f;
	}
	OnScoreChanged.Broadcast(PlayerData.Score);
}

float AUASCharacter::GetScoreMultiplier()
{
	return ScoreMultiplier;
}

float AUASCharacter::GetScore()
{
	return PlayerData.Score;
}

void AUASCharacter::SetScoreMultiplier(float ScoreMultiplier)
{
	this->ScoreMultiplier = ScoreMultiplier;
}

bool AUASCharacter::AddWeapon(FWeaponData& Weapon)
{
	if (!HasWeapon(Weapon))
	{
		Weapons.Add(Weapon);
		return true;
	}
	return false;
}

bool AUASCharacter::HasWeapon(FWeaponData& Weapon)
{
	return Weapons.Contains(Weapon);
}

void AUASCharacter::SwitchPreviousWeapon()
{
	SetWeapon(CurrentWeaponIndex - 1);
}

void AUASCharacter::SwitchNextWeapon()
{
	SetWeapon(CurrentWeaponIndex + 1);
}

void AUASCharacter::SetWeapon(int Index)
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
