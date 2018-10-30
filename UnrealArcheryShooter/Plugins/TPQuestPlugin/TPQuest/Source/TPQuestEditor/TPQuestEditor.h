// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"
#include "TPQuestPrivatePCH.h"
#include "IAssetTools.h"
#include "AssetToolsModule.h"
#include "AssetTypeCategories.h"
#include "SlateStyle.h"

static EAssetTypeCategories::Type QuestCategory = EAssetTypeCategories::Misc;

class FTPQuestEditorModule : public IModuleInterface
{

public:
	static EAssetTypeCategories::Type GetQuestCategory()
	{
		if (QuestCategory == EAssetTypeCategories::Misc)
		{
			IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>(TEXT("AssetTools")).Get();
			QuestCategory = AssetTools.RegisterAdvancedAssetCategory(FName(TEXT("TPQuestCategory")), FText::FromName(TEXT("TPQuest")));
		}
		return QuestCategory;
	}

	// IModuleInterface implementation
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	////////////////////////////////////

protected:
	TSharedPtr<FSlateStyleSet> StyleSet;

	// Set Class Thumbnail - Name is name of icon AND name of class
	void SetClassThumb(FString Name);

	template<class ObjectType>
	void RegisterAssetTypeActions(ObjectType* InObject)
	{
		IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
		TSharedRef<IAssetTypeActions> ObjectiveBehaviorATA = MakeShareable(InObject);
		AssetTools.RegisterAssetTypeActions(ObjectiveBehaviorATA);
	}

};
