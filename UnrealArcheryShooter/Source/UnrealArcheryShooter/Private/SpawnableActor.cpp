// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "SpawnableActor.h"

ASpawnableActor::ASpawnableActor()
{
	PrimaryActorTick.bCanEverTick = true;

	DestructibleMesh = CreateDefaultSubobject<UDestructibleComponent>("Mesh");
	DestructibleMesh->SetSimulatePhysics(true);
	DestructibleMesh->bApplyImpulseOnDamage = true;
	RootComponent = DestructibleMesh;

	Light = CreateDefaultSubobject<UPointLightComponent>("PointLight");
	Light->SetIntensity(10000);
	Light->SetLightColor(FLinearColor::Yellow);
	Light->SetVisibility(true);
	Light->SetSourceLength(1000);
	Light->SetSourceRadius(1500);
	Light->SetSoftSourceRadius(1500);
	Light->SetupAttachment(RootComponent);

	SpawnData = FSpawnData();
}

void ASpawnableActor::BeginPlay()
{
	Super::BeginPlay();
}

void ASpawnableActor::Initialize(FSpawnData SpawnData)
{
	Light->SetLightColor(SpawnData.Color);
	this->SpawnData = SpawnData;
}

float ASpawnableActor::GetScore()
{
	return SpawnData.Score;
}
