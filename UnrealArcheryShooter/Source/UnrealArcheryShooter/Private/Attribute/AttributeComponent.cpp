// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "AttributeComponent.h"

UAttributeComponent::UAttributeComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

	for (TSubclassOf<class UTPAttribute> Attribute : AttributeClasses)
	{
		Attributes.Add(Attribute->GetDefaultObject<UTPAttribute>());
	}

	for (TSubclassOf<class UAutoSkillWorker> WorkerClass : AutoSkillWorkerClasses)
	{
		UAutoSkillWorker* Worker = WorkerClass->GetDefaultObject<UAutoSkillWorker>();
		Worker->Initialize(GetWorld());
		AutoSkillWorkers.Add(Worker);
	}

	if (bFillWorkersWithArray)
	{
		if (Attributes.Num() >= AutoSkillWorkers.Num())
		{
			for (int32 Index = 0; Index < AutoSkillWorkers.Num(); Index++)
			{
				AutoSkillWorkers[Index]->SkillAttribute = Attributes[Index];
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("You can't fill AutoSkillWorkers from Attributes array if there are less attributes than workers"));
		}
	}
}

void UAttributeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	for (UAutoSkillWorker* Worker : AutoSkillWorkers)
	{
		Worker->Tick(DeltaTime);
	}
}
