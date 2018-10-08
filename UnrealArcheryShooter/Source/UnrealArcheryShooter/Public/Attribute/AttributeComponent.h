// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "Components/ActorComponent.h"
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

protected:
	virtual void BeginPlay() override;

private:
	TArray<UTPAttribute*> Attributes;

	UPROPERTY(EditAnywhere)
		TArray<TSubclassOf<class UTPAttribute>> AttributeClasses;

};
