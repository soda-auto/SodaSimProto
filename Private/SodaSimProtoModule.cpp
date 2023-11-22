#pragma once

#include "Modules/ModuleManager.h"
#include "Engine/EngineBaseTypes.h"

class FSodaSimProtoModule : public IModuleInterface
{
public:
	
	virtual void StartupModule() override {}
	virtual void ShutdownModule() override {}
};

IMPLEMENT_MODULE(FSodaSimProtoModule, SodaSimProto)