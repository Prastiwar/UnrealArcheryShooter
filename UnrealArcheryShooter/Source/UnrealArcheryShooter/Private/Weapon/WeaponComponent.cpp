// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "WeaponComponent.h"
#include "Animation/AnimInstance.h"
#include "Projectile.h"
#include "Engine/DataTable.h"
#include "Weapon/UIWeaponData.h"

UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	MeshFreeZoomPosition = FVector(3.293318, -4.998758, -161.327179);
	MeshZoomInPosition = FVector(-17.145920, -17.440310, -155.126846);
}

void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	Cooldown = NewObject<UCooldown>();

	FPMeshViewer = Cast<USkeletalMeshComponent>(FPMeshViewerRef.GetComponent(GetOwner()));
	if (FPMeshViewer)
	{
		AnimInstance = FPMeshViewer->GetAnimInstance();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("FPMeshViewer component not found"));
	}

	GunMesh = Cast<USkeletalMeshComponent>(GunMeshRef.GetComponent(GetOwner()));
	if (!GunMesh)
	{
		UE_LOG(LogTemp, Warning, TEXT("GunMesh component not found"));
	}

	if (Weapons.Num() > 0)
	{
		SetWeapon(CurrentWeaponIndex);
	}
	Zoom(false);
}

void UWeaponComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	Cooldown->Tick(DeltaTime);
}

void UWeaponComponent::Fire()
{
	UWorld* const World = GetWorld();
	if (!Weapons[CurrentWeaponIndex].FireCooldown.bIsCompleted || World == nullptr)
	{
		return;
	}

	FRotator Rotation = GetOwner()->GetActorRotation();
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

	APawn* const OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn)
	{
		Rotation = OwnerPawn->GetControlRotation();
	}

	AProjectile* const Projectile = Weapons[CurrentWeaponIndex].ProjectilePool->PopActor<AProjectile>(GetComponentLocation(), Rotation, SpawnParams);
	if (Projectile)
	{
		UE_LOG(LogTemp, Warning, TEXT("Projectile shoot"));
		OnFire.Broadcast(Projectile);
		if (Weapons[CurrentWeaponIndex].FireCooldown.CooldownTime > 0.0f)
		{
			Cooldown->SetCooldown(&Weapons[CurrentWeaponIndex].FireCooldown);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Fire failed - projectile nullptr"));
	}

	PlayFireAnim();
}

void UWeaponComponent::PlayFireAnim()
{
	if (Weapons[CurrentWeaponIndex].FireAnimation != nullptr)
	{
		if (AnimInstance != nullptr)
		{
			AnimInstance->Montage_Play(Weapons[CurrentWeaponIndex].FireAnimation, 1.f);
		}
	}
}

void UWeaponComponent::ToggleZoom()
{
	bIsZoomed = !bIsZoomed;
	Zoom(bIsZoomed);
}

void UWeaponComponent::Zoom(const bool bToZoom)
{
	if (FPMeshViewer)
	{
		if (bToZoom)
		{
			FPMeshViewer->SetRelativeLocation(MeshZoomInPosition);
		}
		else
		{
			FPMeshViewer->SetRelativeLocation(MeshFreeZoomPosition);
		}
	}
}
bool UWeaponComponent::AddWeapon(FWeaponData& Weapon)
{
	if (!HasWeapon(Weapon))
	{
		Weapon.Initialize(this);
		Weapons.Add(Weapon);
		return true;
	}
	return false;
}

bool UWeaponComponent::HasWeapon(const FWeaponData& Weapon) const
{
	return Weapons.Contains(Weapon);
}

void UWeaponComponent::SetWeapons(const TArray<FWeaponData> OtherWeapons)
{
	Weapons = OtherWeapons;
	for (FWeaponData& Weapon : Weapons)
	{
		Weapon.Initialize(this);
	}
	SetWeapon(CurrentWeaponIndex);
}

void UWeaponComponent::SetWeaponsByNames(const TArray<FName> WeaponNames)
{
	Weapons.Empty(WeaponNames.Num());
	for (FName WeaponName : WeaponNames)
	{
		FUIWeaponData* Weapon = WeaponsTable->FindRow<FUIWeaponData>(WeaponName, TEXT(""));
		if (Weapon)
		{
			AddWeapon(Weapon->Weapon);
		}
	}
	SetWeapon(CurrentWeaponIndex);
}

void UWeaponComponent::SwitchToPreviousWeapon()
{
	SetWeapon(CurrentWeaponIndex - 1);
}

void UWeaponComponent::SwitchToNextWeapon()
{
	SetWeapon(CurrentWeaponIndex + 1);
}

void UWeaponComponent::SetWeapon(const int32 Index)
{
	if (Index >= Weapons.Num())
	{
		CurrentWeaponIndex = 0;
	}
	else if (Index < 0)
	{
		CurrentWeaponIndex = Weapons.Num() - 1;
	}
	else
	{
		CurrentWeaponIndex = Index;
	}
	if (GunMesh)
	{
		GunMesh->SetSkeletalMeshWithoutResettingAnimation(Weapons[CurrentWeaponIndex].WeaponMesh);
	}
	OnWeaponChanged.Broadcast();
}
