// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TPQuest : ModuleRules
{
    public TPQuest(ReadOnlyTargetRules Target) : base(Target)
    {
        MinFilesUsingPrecompiledHeaderOverride = 1;
        bFasterWithoutUnity = true;

        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        bEnforceIWYU = true;

        PublicDependencyModuleNames.AddRange(new string[]{
            "Core", "CoreUObject", "Engine", "AIModule"
        });

        PrivateDependencyModuleNames.AddRange(new string[]{
            "CoreUObject", "Engine"
        });

        PrivateIncludePaths.AddRange(new string[]{
            "TPQuest/Private"
        });
    }
}
