// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "TPQuestEditor.h"
#include "IPluginManager.h"
#include "SlateStyleRegistry.h"
#include "AssetTypeActions.h"

#define LOCTEXT_NAMESPACE "FTPQuestEditorModule"

void FTPQuestEditorModule::StartupModule()
{
	FTPQuestEditorModule::GetQuestCategory();

	// Register all Asset Type Actions
	RegisterAssetTypeActions(new FObjectiveBehaviorFATA);
	RegisterAssetTypeActions(new FQuestFATA);
	RegisterAssetTypeActions(new FQuestComponentFATA);

	FString ContentDir = IPluginManager::Get().FindPlugin("TPQuest")->GetBaseDir();
	StyleSet = MakeShareable(new FSlateStyleSet("TPQuestStyle"));
	StyleSet->SetContentRoot(ContentDir);

	// Set Class Thumbnails - Name is name of icon AND name of class
	SetClassThumb(TEXT("Quest"));
	SetClassThumb(TEXT("ObjectiveBehavior"));
	SetClassThumb(TEXT("QuestComponent"));

	FSlateStyleRegistry::RegisterSlateStyle(*StyleSet);
}

void FTPQuestEditorModule::ShutdownModule()
{
	if (StyleSet)
	{
		FSlateStyleRegistry::UnRegisterSlateStyle(StyleSet->GetStyleSetName());
	}
}

void FTPQuestEditorModule::SetClassThumb(FString Name)
{
	const FVector2D IconSize = FVector2D(128.f, 128.f);
	const TCHAR* IconExt = TEXT(".png");
	const FString IconPath = TEXT("Resources/") + Name;

	FSlateImageBrush* Brush =  new FSlateImageBrush(StyleSet->RootToContentDir(IconPath, IconExt), IconSize);
	if (Brush)
	{
		const FString ClassThumb = "ClassThumbnail.";
		StyleSet->Set(FName(*(ClassThumb + Name)), Brush);
	}
}

IMPLEMENT_MODULE(FTPQuestEditorModule, TPQuestEditor)

#undef LOCTEXT_NAMESPACE
