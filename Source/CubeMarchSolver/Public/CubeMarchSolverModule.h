#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"

class FCubeMarchSolverModule : public IModuleInterface
{
    virtual void StartupModule() override {};
    virtual void ShutdownModule() override {};
};