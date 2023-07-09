// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class RedSpace : ModuleRules
{
	public RedSpace(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		bEnableExceptions = true;

		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"MeshDescription",
				"StaticMeshDescription",
				"MeshConversion",
				"ProceduralMeshComponent",
				"UMG",

				"EnhancedInput",

				"AppFramework",
				"Json",
				"JsonUtilities",
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"InputCore",
				"Slate",
				"SlateCore"
				// ... add private dependencies that you statically link with here ...	
			}
			);


		/*
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"ChaosVehicles", 
			"HeadMountedDisplay", 
			"PhysicsCore",
			"MeshDescription", 
			"StaticMeshDescription", 
			"MeshConversion",
			"RedSpace",
			"RedGeneration",*/
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
