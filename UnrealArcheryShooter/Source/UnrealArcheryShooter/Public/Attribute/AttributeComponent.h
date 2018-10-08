// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "Components/ActorComponent.h"
#include "Attribute/AutoSkillWorker.h"
#include "Attribute/TPAttribute.h"
#include "AttributeComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UNREALARCHERYSHOOTER_API UAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UAttributeComponent();

	UFUNCTION(BlueprintCallable)
		TArray<UTPAttribute*> GetAttributes() { return Attributes; }

	UFUNCTION(BlueprintCallable)
		TArray<UAutoSkillWorker*> GetAutoSkillWorkers() { return AutoSkillWorkers; }

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction);

	TArray<UTPAttribute*> Attributes;
	TArray<UAutoSkillWorker*> AutoSkillWorkers;

	UPROPERTY(EditAnywhere)
		TArray<TSubclassOf<class UAutoSkillWorker>> AutoSkillWorkerClasses;

	UPROPERTY(EditAnywhere)
		TArray<TSubclassOf<class UTPAttribute>> AttributeClasses;

private:
	// Should assign attribute of worker from equivalent indexed attribute?
	UPROPERTY(EditAnywhere)
		bool bFillWorkersWithArray;

};
