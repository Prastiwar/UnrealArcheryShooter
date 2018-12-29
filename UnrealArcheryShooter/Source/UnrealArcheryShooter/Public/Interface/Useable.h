// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "UObject/Interface.h"
#include "Useable.generated.h"

UINTERFACE(MinimalAPI)
class UUseable : public UInterface
{
	GENERATED_BODY()
};

class UNREALARCHERYSHOOTER_API IUseable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void OnUsed(AActor* User);
	virtual void OnUsed_Implementation(AActor* User) {}

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void BeginFocus(AActor* User);
	virtual void BeginFocus_Implementation(AActor* User) {}

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void EndFocus(AActor* User);
	virtual void EndFocus_Implementation(AActor* User) {}

};
