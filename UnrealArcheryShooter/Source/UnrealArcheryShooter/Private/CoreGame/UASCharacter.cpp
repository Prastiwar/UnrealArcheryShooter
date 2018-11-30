// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "UASCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Cooldown/Cooldown.h"
#include "CoreGame/SaveState.h"
#include "ObjectPool/ActorPool.h"
#include "Weapon/WeaponComponent.h"

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

	WeaponComponent = CreateDefaultSubobject<UWeaponComponent>(TEXT("WeaponComponent"));
	WeaponComponent->SetupAttachment(GunMesh);
	WeaponComponent->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));

	AttributeComponent = CreateDefaultSubobject<UAttributeComponent>(TEXT("Attributes"));

	ScoreMultiplier = 1.0f;
	PlayerData = FPlayerData(100);
}

void AUASCharacter::OnFire(UFireBehavior* const FireBehavior)
{
	AddScore(-FireBehavior->GetFireCost());
}

void AUASCharacter::BeginPlay()
{
	Super::BeginPlay();

	//Attach gun mesh component to Skeleton, doing it here because the skeleton is not yet created in the constructor
	GunMesh->AttachToComponent(FirstPersonMeshViewed, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
	FirstPersonMeshViewed->SetHiddenInGame(false, true);

	WeaponComponent->OnFire.AddDynamic(this, &AUASCharacter::OnFire);
	WeaponComponent->SetWeaponsByNames(InitialWeaponsNames);
}

void AUASCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
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
	PlayerInputComponent->BindAction("WheelUp", IE_Pressed, WeaponComponent, &UWeaponComponent::SwitchToNextWeapon);
	PlayerInputComponent->BindAction("WheelDown", IE_Pressed, WeaponComponent, &UWeaponComponent::SwitchToPreviousWeapon);
	PlayerInputComponent->BindAction("E", IE_Pressed, WeaponComponent, &UWeaponComponent::SwitchToNextWeapon);
	PlayerInputComponent->BindAction("Q", IE_Pressed, WeaponComponent, &UWeaponComponent::SwitchToPreviousWeapon);

	// Bind fire events
	PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &UWeaponComponent::Fire);
	PlayerInputComponent->BindAction("Zoom", IE_Pressed, WeaponComponent, &UWeaponComponent::ToggleZoom);

	// Bind Persistence
	PlayerInputComponent->BindAction("SaveGame", IE_Pressed, this, &AUASCharacter::SavePlayer);
	PlayerInputComponent->BindAction("LoadGame", IE_Pressed, this, &AUASCharacter::Load);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &AUASCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveSide", this, &AUASCharacter::MoveSide);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
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
