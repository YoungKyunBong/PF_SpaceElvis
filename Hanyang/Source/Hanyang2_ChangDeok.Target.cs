// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class Hanyang2_ChangDeokTarget : TargetRules
{
	public Hanyang2_ChangDeokTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V4;

		ExtraModuleNames.AddRange( new string[] { "Hanyang2_ChangDeok" } );
	}
}
