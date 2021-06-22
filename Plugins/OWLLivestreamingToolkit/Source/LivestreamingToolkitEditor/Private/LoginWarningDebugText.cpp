// Copyright Off World Live Limited, 2020-2021. All rights reserved.

#include "LoginWarningDebugText.h"
#include "ServerAuth/ServerAuthTool.h"

void FLoginWarningDebugText::Init()
{
	static FLoginWarningDebugText Instance;
}

void FLoginWarningDebugText::Tick(float DeltaTime)
{
	if (UServerAuthTool::Get()->APIConfig.ShouldShowLogInButton())
	{
		GEditor->AddOnScreenDebugMessage(1, 0, FColor(255, 105, 180), TEXT("OWLLivesteamingToolkit: Please Log in to use this plugin."), true);
	}
}

TStatId FLoginWarningDebugText::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(LoginWarningDebugText, STATGROUP_Tickables);
}
