// Copyright Off World Live Limited, 2020-2021. All rights reserved.

using UnrealBuildTool;
using System.IO;

public class LivestreamingToolkit : ModuleRules
{
    public LivestreamingToolkit(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        //Uncomment the line below when distributing the Off World Live plugin without the private directory
        bUsePrecompiled = true;

        // add xxhash
        PrivateIncludePaths.AddRange(
            new string[]
            {
                "ThirdParty/xxhash_cpp"
            }
        );

        string AuthUrl = System.Environment.GetEnvironmentVariable("OWL_AUTH_URL");
        if (AuthUrl == null || AuthUrl == "")
        {
            AuthUrl = "https://plugin-staging-api.offworld.live";
        }
        PublicDefinitions.Add("OWL_AUTH_URL=\"" + AuthUrl + "\"");

        string PublicKey = System.Environment.GetEnvironmentVariable("PUBLIC_KEY");
        if (PublicKey == null)
        {
            PublicKey = "MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEA0h/btD7sxoe6XonVQsUOnxYW8rQUxcCdYEz3zuFOJYJsurkmTTTkNKBT+fVolcNeJh2LxSOB9NPV/4O/ZRnzO5SYE4DzVwyCchYSYQmenf6LtcCTKseassa4Cu/SPcG2eTBH7oejkLB5j7uDWRU2Foeg3G8/a/5YtjMfrpj4bLEhyFBzQlj21MeWv5TkzoLo37AE6rPsoAS0lqIiHi/YPato+pzhyXrkmSTKTSv4eYlqAqkdflEZ+rdLs9v8tzBeCDU9ZvbZcjn5/TiC23XLlaPdQy6NlJDnTVEEJzYEBdQgeJNGoiFQZONrfZQqs0swShbpr9ism3TGIUK+PahD7wIDAQAB";
        }
        PublicDefinitions.Add("PUBLIC_KEY=" + PublicKey);

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "CoreUObject",
                "Engine",
                "RHI",
                "RenderCore",
                "USpout",
                "Projects",
                "Json",
                "JsonUtilities",
                "Http"

				// ... add other public dependencies that you statically link with here ...
			}
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "RenderCore",
                "USpout",
                "CinematicCamera",
                "Slate",
                "UMG",
                "SlateCore",
                "RenderCore",
                "RSA",
                "OpenSSL",
				// ... add private dependencies that you statically link with here ...	
			}
        );

    }
}




