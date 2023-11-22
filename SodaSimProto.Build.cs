using UnrealBuildTool;
using System.Diagnostics;
using System.Collections.Generic;
using System.IO;
using System;

public class SodaSimProto : ModuleRules
{

	public SodaSimProto(ReadOnlyTargetRules Target) : base(Target)
	{
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
                "Core",
                "Engine"
            }
		);

        PublicDefinitions.Add("SODASIMPROTO_WITH_UE");

        if (!Directory.Exists(ModuleDirectory +"/Private"))
        {
            bUsePrecompiled = true;
        }
    }
}
