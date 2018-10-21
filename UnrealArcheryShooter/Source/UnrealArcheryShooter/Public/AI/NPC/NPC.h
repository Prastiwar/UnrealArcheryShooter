// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "GameFramework/Character.h"
#include "NPC.generated.h"

UCLASS()
class UNREALARCHERYSHOOTER_API ANPC : public ACharacter
{
	GENERATED_BODY()

public:
	ANPC();

	UPROPERTY(EditAnywhere)
		class UBehaviorTree* BehaviourTree;

};
