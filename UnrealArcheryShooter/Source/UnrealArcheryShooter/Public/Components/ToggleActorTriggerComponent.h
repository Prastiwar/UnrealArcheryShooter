// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "Toggle.h"
#include "Components/ActorComponent.h"
#include "ToggleActorTriggerComponent.generated.h"

UCLASS(ClassGroup = (Trigger), meta = (BlueprintSpawnableComponent))
class UNREALARCHERYSHOOTER_API UToggleActorTriggerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UToggleActorTriggerComponent();

	UFUNCTION(BlueprintCallable)
		void SetTarget(AActor* const NewTarget);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool bHiddenOnStart;

	// Active on Trigger Enter or on Trigger Exit?
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool bActiveOnEnter;

	FToggle Toggle;
	AActor* TargetActor;
	class ITrigger* Trigger;

	virtual void BeginPlay() override;

	void BeginTrigger(AActor* OtherActor, UPrimitiveComponent* OtherComp);
	void EndTrigger(AActor* OtherActor, UPrimitiveComponent* OtherComp);

private:
	UPROPERTY(EditAnywhere)
		FComponentReference TriggerComponentRef;

};
