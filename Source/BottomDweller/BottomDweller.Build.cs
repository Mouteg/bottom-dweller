// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BottomDweller : ModuleRules
{
	public BottomDweller(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new [] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "UMG", "EnhancedInput" });
		PublicDependencyModuleNames.AddRange(new [] { "GameplayAbilities", "GameplayTags", "GameplayTasks" });
	}
}
