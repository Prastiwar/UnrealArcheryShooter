// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "Weapon/FireBehavior.h"
#include "UASFireBehavior.generated.h"

UCLASS()
class UNREALARCHERYSHOOTER_API UUASFireBehavior : public UFireBehavior
{
	GENERATED_BODY()

protected:
	virtual void OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, const FHitResult& Hit) override;

	virtual void OnExplode(TArray<FHitResult> HitResults);

private:
	bool TryAddScoreFromActor(AActor* OtherActor);

};
