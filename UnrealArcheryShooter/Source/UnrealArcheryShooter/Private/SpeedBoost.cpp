// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "SpeedBoost.h"
#include "UASCharacter.h"

ASpeedBoost::ASpeedBoost()
{
	PrimaryActorTick.bCanEverTick = false;
	BoxTrigger = CreateDefaultSubobject<UBoxComponent>("BoxTrigger");
	SetTriggerComponent(BoxTrigger);
}

void ASpeedBoost::PickBoostImpl(AActor* AppliedActor)
{
	AUASCharacter* Player = Cast<AUASCharacter>(AppliedActor);
	if (Player)
	{
		TArray<UCharacterMovementComponent*> MoveComponents;
		Player->GetComponents<UCharacterMovementComponent>(MoveComponents);

		if (MoveComponents.IsValidIndex(0))
		{
			MoveComponents[0]->MaxWalkSpeed += Boost.Power;
		}
	}
}

void ASpeedBoost::RevertBoostImpl(AActor* AppliedActor)
{
	AUASCharacter* Player = Cast<AUASCharacter>(AppliedActor);
	if (Player)
	{
		TArray<UCharacterMovementComponent*> MoveComponents;
		Player->GetComponents<UCharacterMovementComponent>(MoveComponents);

		if (MoveComponents.IsValidIndex(0))
		{
			MoveComponents[0]->MaxWalkSpeed -= Boost.Power;
		}
	}
}

