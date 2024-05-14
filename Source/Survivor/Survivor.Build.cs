// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Survivor : ModuleRules
{
	public Survivor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new[]
		{
			"Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "NavigationSystem", "AIModule", "Niagara", "EnhancedInput", "GameplayAbilities",
			"GameplayTags", "GameplayTasks"
		});
	}
}