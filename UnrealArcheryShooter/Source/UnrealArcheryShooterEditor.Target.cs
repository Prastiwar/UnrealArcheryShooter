// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

using UnrealBuildTool;
using System.Collections.Generic;

public class UnrealArcheryShooterEditorTarget : TargetRules
{
	public UnrealArcheryShooterEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "UnrealArcheryShooter", "TPMeasure", "ApexDestruction" } );
	}
}
