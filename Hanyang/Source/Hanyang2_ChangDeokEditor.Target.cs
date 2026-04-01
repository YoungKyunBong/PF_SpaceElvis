// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class Hanyang2_ChangDeokEditorTarget : TargetRules
{
	public Hanyang2_ChangDeokEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V4;

		ExtraModuleNames.AddRange( new string[] { "Hanyang2_ChangDeok" } );
	}
}
