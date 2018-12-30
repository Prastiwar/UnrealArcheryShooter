// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "Engine/Classes/Kismet/GameplayStatics.h"

struct UNREALARCHERYSHOOTER_API FStatics
{
	/** Get casted component from FComponentReferende, if not found, will send warning */
	template<typename T>
	static T* GetComponent(FComponentReference Reference, AActor* OwningActor)
	{
		T* Component = Cast<T>(Reference.GetComponent(OwningActor));
		if (!Component)
		{
			UE_LOG(LogTemp, Warning, TEXT("Component not found %s"), *OwningActor->GetName());
		}
		return Component;
	}

	/** Get casted component from OwningActor, if not found, will send warning */
	template<typename T>
	static T* GetComponentByClass(AActor* OwningActor)
	{
		T* Component = Cast<T>(OwningActor->GetComponentByClass(T::StaticClass()));
		if (!Component)
		{
			UE_LOG(LogTemp, Warning, TEXT("Component not found %s"), *OwningActor->GetName());
		}
		return Component;
	}

	template<typename T>
	static TScriptInterface<T> CreateScriptInterface(T* InInterface, UObject* InObject)
	{
		auto ScriptInterface = TScriptInterface<T>();
		ScriptInterface.SetInterface(InInterface);
		ScriptInterface.SetObject(InObject);
		return ScriptInterface;
	}

};
