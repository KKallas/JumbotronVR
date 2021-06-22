// Copyright Off World Live Limited, 2020-2021. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SWidget.h"
#include "Framework/Commands/UICommandList.h"
#include "Editor/LevelEditor/Private/SLevelEditor.h"
#include "Modules/ModuleManager.h"
#include "ServerAuth/APIConfiguration.h"

class FToolBarBuilder;
class FMenuBuilder;

class FLivestreamingToolkitEditorModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	/** This function will be bound to Command. */
	void LogInButtonClicked();
	void LogOutButtonClicked();
	void AboutButtonClicked();
	void VisitDocsButtonClicked();
	void VisitWebsiteButtonClicked();
	void VisitDiscordButtonClicked();
	void VisitYoutubeButtonClicked();
	
private:

	void RegisterMenus();


	bool IsLogInButtonVisible();
	bool IsLogOutButtonVisible();
private:
	TSharedPtr<class FUICommandList> PluginCommands;
	TSharedRef<SWidget> FillComboButton(TSharedPtr<class FUICommandList> Commands);
};
