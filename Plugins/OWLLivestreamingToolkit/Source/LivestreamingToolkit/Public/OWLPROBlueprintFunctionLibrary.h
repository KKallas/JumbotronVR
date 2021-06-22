// Copyright Off World Live Limited, 2020-2021. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "OWLPROBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class LIVESTREAMINGTOOLKIT_API UOWLPROBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	/**
	 * Use this to render any UMG Widets
	 */
	UFUNCTION(Category = "OWL Livestreaming Toolkit", BlueprintCallable)
	static void DrawUMGToRenderTarget(UUserWidget* UMGWidget, FIntPoint Size, float DeltaTime, UPARAM(ref) UTextureRenderTarget2D* RenderTarget);

	/**
	* bind this function to the key of your choice to create a way to log in in packaged games
	*/
	UFUNCTION(Category = "OWL Livestreaming Toolkit", BlueprintCallable)
	static void OWLLogIn();

	/**
	* bind this function to the key of your choice to create a way to log in in packaged games
	*/
	UFUNCTION(Category = "OWL Livestreaming Toolkit", BlueprintCallable)
	static void OWLLogOut();

	/**
	* this fuction will return true if the user is logged in and false if they are logged out
	*/
	UFUNCTION(Category = "OWL Livestreaming Toolkit", BlueprintCallable)
	static bool OWLLogInStatus();
};
