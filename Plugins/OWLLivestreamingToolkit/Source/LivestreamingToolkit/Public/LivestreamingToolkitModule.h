// Copyright Off World Live Limited, 2020-2021. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "ServerAuth/APIConfiguration.h"

DECLARE_LOG_CATEGORY_EXTERN(LivestreamingToolkitLog, Log, All);

class FLivestreamingToolkitModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	FDelegateHandle OnFEngineLoopInitCompleteHandle;
	void OnFEngineLoopInitComplete();
	FDelegateHandle OnAuthRequestLoginHandle;
	void OnAuthRequestLogin();
	FDelegateHandle OnPreExitHandle;
	void OnPreExit();
};
