// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "Attribute/AutoSkillWorker.h"
#include "RunSkillWorker.generated.h"

UCLASS(Blueprintable, BlueprintType)
class UNREALARCHERYSHOOTER_API URunSkillWorker : public UAutoSkillWorker
{
	GENERATED_BODY()

public:
	virtual void Initialize(const UWorld* World) override;
	virtual void Tick(const float DeltaSeconds) override;
	virtual void ModifyAttribute() override;

protected:
	// Time to run before collecting a point
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 InitialRunTime = 1;

	int32 RunTime;
	class AUASCharacter* Player;
	const UWorld* World;

};
