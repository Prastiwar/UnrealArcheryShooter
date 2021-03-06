// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "SpawnableRing.h"
#include "Components/PointLightComponent.h"

ASpawnableRing::ASpawnableRing()
{
	DestructibleMesh = CreateDefaultSubobject<UDestructibleComponent>("Mesh");
	DestructibleMesh->GetBodyInstance()->SetInstanceSimulatePhysics(true);
	DestructibleMesh->bApplyImpulseOnDamage = true;
	DestructibleMesh->SetMobility(EComponentMobility::Movable);

	RootComponent = DestructibleMesh;

	Light = CreateDefaultSubobject<UPointLightComponent>("PointLight");
	Light->SetIntensity(10000);
	Light->SetLightColor(FLinearColor::Yellow);
	Light->SetVisibility(true);
	Light->SetSourceLength(1000);
	Light->SetSourceRadius(1500);
	Light->SetSoftSourceRadius(1500);
	Light->SetupAttachment(DestructibleMesh);
}

bool ASpawnableRing::CanBeSpawned() const
{
	Light->SetLightColor(FLinearColor::MakeRandomColor());
	return ISpawnable::CanBeSpawned();
}

float ASpawnableRing::GetScore() const
{
	return FMath::RandRange(10.0f, 200.0f);
}
