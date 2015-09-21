// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class ULPlot : ModuleRules
{
	public ULPlot(TargetInfo Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

        PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore", "UMG" });

        //Private Paths
        PrivateIncludePaths.AddRange(new string[] {
			"ULPlot/Private"
		});
	}
}
