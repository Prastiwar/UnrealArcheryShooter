// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "ScoreBoost.h"

AScoreBoost::AScoreBoost()
{
	PrimaryActorTick.bCanEverTick = false;
	BoxTrigger = CreateDefaultSubobject<UBoxComponent>("BoxTrigger");
	SetTriggerComponent(BoxTrigger);
}

void AScoreBoost::PickBoostImpl(AActor* AppliedActor)
{
	AUASCharacter* Player = Cast<AUASCharacter>(AppliedActor);
	if (Player)
	{
		Player->SetScoreMultiplier(Player->GetScoreMultiplier() + Boost.Power);
	}
}

void AScoreBoost::RevertBoostImpl(AActor* AppliedActor)
{
	AUASCharacter* Player = Cast<AUASCharacter>(AppliedActor);
	if (Player)
	{
		Player->SetScoreMultiplier(Player->GetScoreMultiplier() - Boost.Power);
	}
}
