// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GASPrototype : ModuleRules
{
	public GASPrototype(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput",

			//UI
			"UMG", 

			//GAS
			"GameplayAbilities", "GameplayTags", "GameplayTasks", 
			
			//AI
			"AIModule",

			//Online
			"OnlineSubsystem", "OnlineSubsystemUtils",
		});

		PrivateDependencyModuleNames.AddRange(new string[] { "AdvancedSessions" });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
