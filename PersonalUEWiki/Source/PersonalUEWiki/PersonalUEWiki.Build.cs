// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class PersonalUEWiki : ModuleRules
{
	public PersonalUEWiki(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "GameplayTags"});
	}
}
