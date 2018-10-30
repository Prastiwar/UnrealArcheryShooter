// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/TPQuestPlugin

#pragma once

#include "AssetTypeActions.h"
#include "TPQuestBlueprintFactory.h"
#include "TPQuestFactories.generated.h"

UCLASS()
class TPQUESTEDITOR_API UQuestFactory : public UTPQuestBlueprintFactory
{
	GENERATED_BODY()

public:
	UQuestFactory()
	{
		TitleText = FText::FromName(TEXT("Pick Quest Class"));
		SupportedClass = UQuest::StaticClass();
	}
};

UCLASS()
class TPQUESTEDITOR_API UObjectiveFactory : public UTPQuestBlueprintFactory
{
	GENERATED_BODY()

public:
	UObjectiveFactory()
	{
		TitleText = FText::FromName(TEXT("Pick Objective Behavior Class"));
		SupportedClass = UObjectiveBehavior::StaticClass();
	}
};

UCLASS()
class TPQUESTEDITOR_API UQuestComponentFactory : public UTPQuestBlueprintFactory
{
	GENERATED_BODY()

public:
	UQuestComponentFactory()
	{
		TitleText = FText::FromName(TEXT("Pick Quest Component Class"));
		SupportedClass = UQuestComponent::StaticClass();
	}
};