// Copyright Off World Live Limited, 2020-2021. All rights reserved.

#include "LivestreamingToolkitEditor.h"
#include "LivestreamingToolkitEditorStyle.h"
#include "LivestreamingToolkitEditorCommands.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"
#include "Interfaces/IPluginManager.h"
#include "ProjectDescriptor.h"
#include "ServerAuth/ServerAuthTool.h"
#include "LoginWarningDebugText.h"

#define LOCTEXT_NAMESPACE "FLivestreamingToolkitEditorModule"

void FLivestreamingToolkitEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FLivestreamingToolkitEditorStyle::Initialize();
	FLivestreamingToolkitEditorStyle::ReloadTextures();

	FLivestreamingToolkitEditorCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FLivestreamingToolkitEditorCommands::Get().LogIn,
		FExecuteAction::CreateRaw(this, &FLivestreamingToolkitEditorModule::LogInButtonClicked),
		FCanExecuteAction(),
		FGetActionCheckState(),
		FIsActionButtonVisible::CreateRaw(this, &FLivestreamingToolkitEditorModule::IsLogInButtonVisible));

	PluginCommands->MapAction(
		FLivestreamingToolkitEditorCommands::Get().LogOut,
		FExecuteAction::CreateRaw(this, &FLivestreamingToolkitEditorModule::LogOutButtonClicked),
		FCanExecuteAction(),
		FGetActionCheckState(),
		FIsActionButtonVisible::CreateRaw(this, &FLivestreamingToolkitEditorModule::IsLogOutButtonVisible));

	PluginCommands->MapAction(
		FLivestreamingToolkitEditorCommands::Get().About,
		FExecuteAction::CreateRaw(this, &FLivestreamingToolkitEditorModule::AboutButtonClicked),
		FCanExecuteAction());

	PluginCommands->MapAction(
		FLivestreamingToolkitEditorCommands::Get().VisitDocs,
		FExecuteAction::CreateRaw(this, &FLivestreamingToolkitEditorModule::VisitDocsButtonClicked),
		FCanExecuteAction());

	PluginCommands->MapAction(
		FLivestreamingToolkitEditorCommands::Get().VisitWebsite,
		FExecuteAction::CreateRaw(this, &FLivestreamingToolkitEditorModule::VisitWebsiteButtonClicked),
		FCanExecuteAction());

	PluginCommands->MapAction(
		FLivestreamingToolkitEditorCommands::Get().VisitDiscord,
		FExecuteAction::CreateRaw(this, &FLivestreamingToolkitEditorModule::VisitDiscordButtonClicked),
		FCanExecuteAction());

	PluginCommands->MapAction(
		FLivestreamingToolkitEditorCommands::Get().VisitYoutube,
		FExecuteAction::CreateRaw(this, &FLivestreamingToolkitEditorModule::VisitYoutubeButtonClicked),
		FCanExecuteAction());


	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FLivestreamingToolkitEditorModule::RegisterMenus));

	FLoginWarningDebugText::Init();
}

void FLivestreamingToolkitEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FLivestreamingToolkitEditorStyle::Shutdown();

	FLivestreamingToolkitEditorCommands::Unregister();


}

void FLivestreamingToolkitEditorModule::LogInButtonClicked()
{
	UServerAuthTool* tool = UServerAuthTool::Get();

	if (tool->APIConfig.ShouldShowLogInButton())
	{
		tool->Login();
	}
}

void FLivestreamingToolkitEditorModule::LogOutButtonClicked()
{
	UServerAuthTool* tool = UServerAuthTool::Get();

	if (tool->APIConfig.ShouldShowLogOutButton())
	{
		tool->LogOut();
	}
}

void FLivestreamingToolkitEditorModule::AboutButtonClicked()
{
	FString PluginVersion = FString("");
	FString EngineVersion = FString("");
	TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin("OWLLivestreamingToolkit");
	if (Plugin.IsValid())
	{
		FPluginDescriptor Desc = Plugin->GetDescriptor();
		PluginVersion = Desc.VersionName;
		EngineVersion = Desc.EngineVersion;
	}

	FText DialogText = FText::Format(
		LOCTEXT("PluginButtonDialogText", "Plugin Version: {0} \nEngine Version: {1}"),
		FText::FromString(PluginVersion),
		FText::FromString(EngineVersion)
	);
	FMessageDialog::Open(EAppMsgType::Ok, DialogText);
}

void FLivestreamingToolkitEditorModule::VisitDocsButtonClicked()
{
	// TODO : Replace with docs url
	FString URL = FString(TEXT("https://docs.offworld.live/#/"));
	FPlatformProcess::LaunchURL(*URL, nullptr, nullptr);
}

void FLivestreamingToolkitEditorModule::VisitWebsiteButtonClicked()
{
	FString URL = FString(TEXT("https://offworld.live/"));
	FPlatformProcess::LaunchURL(*URL, nullptr, nullptr);
}

void FLivestreamingToolkitEditorModule::VisitDiscordButtonClicked()
{
	FString URL = FString(TEXT("https://discord.com/invite/44M8YhSaPE"));
	FPlatformProcess::LaunchURL(*URL, nullptr, nullptr);
}

void FLivestreamingToolkitEditorModule::VisitYoutubeButtonClicked()
{
	FString URL = FString(TEXT("https://www.youtube.com/channel/UCH7tXF84-FckIQcyIGfRfZQ"));
	FPlatformProcess::LaunchURL(*URL, nullptr, nullptr);
}

void FLivestreamingToolkitEditorModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);
	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				Section.AddEntry(FToolMenuEntry::InitComboButton(
					"Off World Live",
					FUIAction(),
					FOnGetContent::CreateRaw(this, &FLivestreamingToolkitEditorModule::FillComboButton, PluginCommands),
					LOCTEXT("OffWorldLiveBtn", "Off World Live"),
					LOCTEXT("OffWorldLiveBtnTootlip", "Off World Live"),
					FSlateIcon(FLivestreamingToolkitEditorStyle::GetStyleSetName(), "OWLLiveStreamingToolkit.PluginTaskbarIcon")
				));
			}
		}
	}
}

bool FLivestreamingToolkitEditorModule::IsLogInButtonVisible()
{
	return UServerAuthTool::Get()->APIConfig.ShouldShowLogInButton();
}

bool FLivestreamingToolkitEditorModule::IsLogOutButtonVisible()
{
	return UServerAuthTool::Get()->APIConfig.ShouldShowLogOutButton();
}

TSharedRef<SWidget> FLivestreamingToolkitEditorModule::FillComboButton(TSharedPtr<class FUICommandList> Commands)
{
	FMenuBuilder MenuBuilder(true, Commands);

	MenuBuilder.AddMenuEntry(FLivestreamingToolkitEditorCommands::Get().LogIn);
	MenuBuilder.AddMenuEntry(FLivestreamingToolkitEditorCommands::Get().LogOut);
	MenuBuilder.AddMenuEntry(FLivestreamingToolkitEditorCommands::Get().About);
	MenuBuilder.AddMenuEntry(FLivestreamingToolkitEditorCommands::Get().VisitDocs);
	MenuBuilder.AddMenuSeparator();
	MenuBuilder.AddMenuEntry(FLivestreamingToolkitEditorCommands::Get().VisitWebsite);
	MenuBuilder.AddMenuEntry(FLivestreamingToolkitEditorCommands::Get().VisitDiscord);
	MenuBuilder.AddMenuEntry(FLivestreamingToolkitEditorCommands::Get().VisitYoutube);

	return MenuBuilder.MakeWidget();
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FLivestreamingToolkitEditorModule, LivestreamingToolkitEditor)