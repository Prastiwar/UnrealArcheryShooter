// // Copyright 2018-2019 Tomasz Piowczyk, MIT License

#include "PointLightSwitcher.h"


// Sets default values
APointLightSwitcher::APointLightSwitcher()
{
	PrimaryActorTick.bCanEverTick = false;

	Box = CreateDefaultSubobject<UBoxComponent>("PointLightBox");
	Box->InitBoxExtent(FVector(50, 50, 50));
	Box->OnComponentBeginOverlap.AddDynamic(this, &APointLightSwitcher::BeginOverlap);
	Box->OnComponentEndOverlap.AddDynamic(this, &APointLightSwitcher::EndOverlap);

	RootComponent = Box;

	PointLight = CreateDefaultSubobject<UPointLightComponent>("PointLight");
	PointLight->SetupAttachment(Box);
}

// Called when the game starts or when spawned
void APointLightSwitcher::BeginPlay()
{
	Super::BeginPlay();
}

void APointLightSwitcher::BeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
	{
		PointLight->SetVisibility(true);
	}
}

void APointLightSwitcher::EndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex)
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
	{
		PointLight->SetVisibility(false);
	}
}
