// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "RunSkillWorker.h"

void URunSkillWorker::Initialize(const UWorld* World)
{
	SkillAttribute = SkillAttributeClass->GetDefaultObject<UTPAttribute>();
	RunTime = InitialRunTime;
	this->World = World;
	Player = AUASCharacter::GetUASCharacter(World);
}

void URunSkillWorker::Tick(const float DeltaSeconds)
{
	if (!Player->GetVelocity().IsZero())
	{
		RunTime -= DeltaSeconds;
		if (RunTime <= 0.0f)
		{
			ModifyAttribute();
			RunTime = InitialRunTime;
		}
	}
}

void URunSkillWorker::ModifyAttribute()
{
	SkillAttribute->Add(Modifier);
}
