using UnrealBuildTool;

public class NetworkShooterGame : ModuleRules
{
    public NetworkShooterGame(ReadOnlyTargetRules Target ) : base( Target )
		{
			PublicDependencyModuleNames.AddRange( new string[] {"Core",
																"Engine",
																"CoreUObject",
																"InputCore",
																"EnhancedInput",
																"GameplayAbilities",
																"GameplayTags",
																"GameplayTasks"
			} );

			PrivateDependencyModuleNames.AddRange(new string[] {"RenderCore",
																"UMG",
																"Slate",
																"SlateCore",
																"OnlineSubsystem"});
		}
	}