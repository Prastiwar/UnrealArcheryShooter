// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "SpawnableRing.h"

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

bool ASpawnableRing::CanBeSpawned()
{
	Light->SetLightColor(FLinearColor::MakeRandomColor());
	return true;
}

float ASpawnableRing::GetScore()
{
	return FMath::RandRange(10.0f, 200.0f);
}
