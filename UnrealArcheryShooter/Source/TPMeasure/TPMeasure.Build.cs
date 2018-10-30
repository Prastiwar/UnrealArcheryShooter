// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/

using UnrealBuildTool;

public class TPMeasure : ModuleRules
{
	public TPMeasure(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] {
            "Core", "CoreUObject", "Engine", "InputCore"
        });
	}
}
