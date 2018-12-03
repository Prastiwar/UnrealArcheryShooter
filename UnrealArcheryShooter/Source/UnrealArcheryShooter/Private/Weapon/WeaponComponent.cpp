// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "WeaponComponent.h"
#include "Animation/AnimInstance.h"
#include "Engine/DataTable.h"
#include "Weapon/UIWeaponData.h"
#include "Weapon/FireBehavior.h"

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

	Camera = Cast<UCameraComponent>(CameraRef.GetComponent(GetOwner()));
	if (!Camera)
	{
		UE_LOG(LogTemp, Warning, TEXT("Camera component not found"));
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
	if (!Weapons[CurrentWeaponIndex].FireCooldown.bIsCompleted)
	{
		return;
	}

	Weapons[CurrentWeaponIndex].FireBehavior->Fire(GetOwner(), GetComponentLocation(), Camera->GetForwardVector());
	OnFire.Broadcast(Weapons[CurrentWeaponIndex].FireBehavior);
	if (Weapons[CurrentWeaponIndex].FireCooldown.CooldownTime > 0.0f)
	{
		Cooldown->SetCooldown(&Weapons[CurrentWeaponIndex].FireCooldown);
	}
	PlayFireAnim();
}

void UWeaponComponent::PlayFireAnim()
{
	if (Weapons[CurrentWeaponIndex].FireBehavior->GetFireAnimation() != nullptr)
	{
		if (AnimInstance != nullptr)
		{
			AnimInstance->Montage_Play(Weapons[CurrentWeaponIndex].FireBehavior->GetFireAnimation(), 1.f);
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
		Weapon.Initialize();
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
		Weapon.Initialize();
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
