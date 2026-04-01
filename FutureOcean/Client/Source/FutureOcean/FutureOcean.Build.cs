// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FutureOcean : ModuleRules
{
	public FutureOcean(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore","UMG", "MediaAssets", "Slate", "SlateCore", "EnhancedInput", "Networking", "Sockets", "AIModule", "ImageWrapper", "RenderCore", "RHI", "Niagara", "LiveLinkInterface", "LiveLink", "LiveLinkComponents" });

		PrivateDependencyModuleNames.AddRange(new string[] { });
		
	}
}
