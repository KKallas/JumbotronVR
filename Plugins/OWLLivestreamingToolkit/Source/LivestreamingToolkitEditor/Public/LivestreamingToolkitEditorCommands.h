// Copyright Off World Live Limited, 2020-2021. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "LivestreamingToolkitEditorStyle.h"

class FLivestreamingToolkitEditorCommands : public TCommands<FLivestreamingToolkitEditorCommands>
{
public:

	FLivestreamingToolkitEditorCommands()
		: TCommands<FLivestreamingToolkitEditorCommands>(TEXT("LivestreamingToolkitEditor"), NSLOCTEXT("Contexts", "LivestreamingToolkitEditor", "OWLLivestreamingToolkit Plugin"), NAME_None, FLivestreamingToolkitEditorStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr<FUICommandInfo> LogIn;
	TSharedPtr<FUICommandInfo> LogOut;
	TSharedPtr<FUICommandInfo> About;
	TSharedPtr<FUICommandInfo> VisitDocs;
	TSharedPtr<FUICommandInfo> VisitWebsite;
	TSharedPtr<FUICommandInfo> VisitDiscord;
	TSharedPtr<FUICommandInfo> VisitYoutube;
};
