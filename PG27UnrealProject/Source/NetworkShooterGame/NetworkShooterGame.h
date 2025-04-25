#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"

class FNetworkShooterGameModule : public IModuleInterface
{
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};