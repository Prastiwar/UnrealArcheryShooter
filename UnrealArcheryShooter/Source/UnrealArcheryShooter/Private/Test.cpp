// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "Test.h"

ATest::ATest()
{
	DestructibleComponent = CreateDefaultSubobject<UDestructibleComponent>("DMComp");
	Light = CreateDefaultSubobject<UPointLightComponent>("Light");
	DestructibleComponent->SetSimulatePhysics(true);
	GLog->Log(DestructibleComponent->IsSimulatingPhysics() ? TEXT("true") : TEXT("false")); // shows "false"
	RootComponent = DestructibleComponent;
	Light->SetupAttachment(RootComponent);
}

void ATest::BeginPlay()
{
	Super::BeginPlay();
	GLog->Log(DestructibleComponent->IsSimulatingPhysics() ? TEXT("true") : TEXT("false")); // Shows "false"
	//DestructibleComponent->SetSimulatePhysics(true); // without this line Actor does not fall down
	GLog->Log(DestructibleComponent->IsSimulatingPhysics() ? TEXT("true") : TEXT("false")); // Shows "false", but actor falls down
}
