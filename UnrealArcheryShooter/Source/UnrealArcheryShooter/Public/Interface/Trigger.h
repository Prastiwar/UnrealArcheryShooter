// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "UObject/Interface.h"
#include "Trigger.generated.h"

UINTERFACE(MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))
class UTrigger : public UInterface
{
	GENERATED_BODY()
};

class UNREALARCHERYSHOOTER_API ITrigger
{
	GENERATED_BODY()
		DECLARE_DELEGATE_TwoParams(FTriggerPhase, AActor*, UPrimitiveComponent*)

public:
	template <typename UserClass>
	void BindTrigger(UserClass* InUserObject,
		typename TMemFunPtrType<false, UserClass, void(AActor*, UPrimitiveComponent*)>::Type EnterTriggerFunc,
		typename TMemFunPtrType<false, UserClass, void(AActor*, UPrimitiveComponent*)>::Type ExitTriggerFunc)
	{
		if (EnterTriggerFunc)
		{
			OnTriggerEnter.BindUObject(InUserObject, EnterTriggerFunc);
		}
		if (ExitTriggerFunc)
		{
			OnTriggerExit.BindUObject(InUserObject, ExitTriggerFunc);
		}
	}

	UFUNCTION()
		virtual void BeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, const int32 OtherBodyIndex, const bool bFromSweep, const FHitResult& SweepResult)
		{
			OnTriggerEnter.ExecuteIfBound(OtherActor, OtherComp);
		}

	UFUNCTION()
		virtual void EndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, const int32 OtherBodyIndex)
		{
			OnTriggerExit.ExecuteIfBound(OtherActor, OtherComp);
		}

protected:
	FTriggerPhase OnTriggerEnter;
	FTriggerPhase OnTriggerExit;

};
