// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System;
using System.IO;
using System.IO.Compression;

public class Hanyang2_ChangDeok : ModuleRules
{
	public Hanyang2_ChangDeok(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "MediaAssets", "UMG", "Slate", "SlateCore", "Http" });

		PrivateDependencyModuleNames.AddRange(new string[] { });

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
