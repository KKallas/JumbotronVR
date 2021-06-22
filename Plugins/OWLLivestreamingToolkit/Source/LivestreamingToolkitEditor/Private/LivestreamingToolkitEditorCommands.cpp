// Copyright Off World Live Limited, 2020-2021. All rights reserved.

#include "LivestreamingToolkitEditorCommands.h"

#define LOCTEXT_NAMESPACE "FLivestreamingToolkitEditorModule"

void FLivestreamingToolkitEditorCommands::RegisterCommands()
{
	UI_COMMAND(LogIn, "Log In", "Log In to OWL Server", EUserInterfaceActionType::Button, FInputGesture());
	UI_COMMAND(LogOut, "Log Out", "Log In to OWL Server", EUserInterfaceActionType::Button, FInputGesture());
	UI_COMMAND(About, "About", "Show Plugin Info", EUserInterfaceActionType::Button, FInputGesture());
	UI_COMMAND(VisitDocs, "View Documentation", "View Documentation", EUserInterfaceActionType::Button, FInputGesture());
	UI_COMMAND(VisitWebsite, "Visit Our Website", "Visit Our Website", EUserInterfaceActionType::Button, FInputGesture());
	UI_COMMAND(VisitDiscord, "Visit Our Discord", "Visit Our Discord", EUserInterfaceActionType::Button, FInputGesture());
	UI_COMMAND(VisitYoutube, "Visit Our Youtube", "Visit Our Youtube", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
