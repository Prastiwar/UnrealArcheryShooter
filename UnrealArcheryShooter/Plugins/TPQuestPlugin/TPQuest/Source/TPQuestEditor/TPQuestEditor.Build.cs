// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TPQuestEditor : ModuleRules
{
    public TPQuestEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        MinFilesUsingPrecompiledHeaderOverride = 1;
        bFasterWithoutUnity = true;

        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        bEnforceIWYU = true;

        PublicDependencyModuleNames.AddRange(new string[]{
            "Core", "CoreUObject", "Engine", "AssetTools", "Slate", "ClassViewer", "UnrealEd", "TPQuest"
        });

        PrivateDependencyModuleNames.AddRange(new string[]{
            "CoreUObject", "Engine", "Slate", "SlateCore", "Projects", "UnrealEd", "AssetTools", "TPQuest"
        });

        PrivateIncludePaths.AddRange(new string[]{
            "TPQuestEditor/Private", "TPQuest/Private"
        });
    }
}
