// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

using UnrealBuildTool;
using System.Collections.Generic;

public class UnrealArcheryShooterTarget : TargetRules
{
	public UnrealArcheryShooterTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "UnrealArcheryShooter", "TPMeasure" } );
	}
}
