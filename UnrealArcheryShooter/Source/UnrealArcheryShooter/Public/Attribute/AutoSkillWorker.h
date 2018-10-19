// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "Attribute/TPAttribute.h"
#include "AutoSkillWorker.generated.h"

UCLASS(BlueprintType, Abstract)
class UNREALARCHERYSHOOTER_API UAutoSkillWorker : public UObject
{
	GENERATED_BODY()

public:
	UAutoSkillWorker() { Modifier.Source = this; }
	~UAutoSkillWorker() {}

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		struct FTPModifier Modifier;

	UTPAttribute* SkillAttribute;

	virtual void Initialize(const UWorld* World) { unimplemented(); }
	virtual void Tick(const float DeltaSeconds) { unimplemented(); }
	virtual void ModifyAttribute() { unimplemented(); }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TSubclassOf<class UTPAttribute> SkillAttributeClass;
};
