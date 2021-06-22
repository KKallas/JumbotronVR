// Copyright Off World Live Limited, 2020-2021. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "CineCameraComponent.h"
#include "Engine/TextureRenderTarget2D.h"

#include "HAL/CriticalSection.h"

#include "ServerAuth/APIConfiguration.h"

#include "OWLCineCamCaptureComponent.generated.h"

class FSceneViewStateInterface;

UCLASS(hidecategories = (Collision, Object, Physics, SceneComponent, Mobility), ClassGroup = Rendering, editinlinenew, meta = (BlueprintSpawnableComponent))
class LIVESTREAMINGTOOLKIT_API UOWLCineCamCaptureComponent : public UCineCameraComponent
{
	GENERATED_BODY()

public:
	UOWLCineCamCaptureComponent(const FObjectInitializer& ObjectInitializer);

	/**
	* Render target to render into and send to Spout
	* If left unset the render target will be generated automatically
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Current Camera Settings")
	UTextureRenderTarget2D* TextureTarget = nullptr;

	/**
	* Min: 64px, Max: 7680
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Current Camera Settings", meta = (EditCondition = "!bConstrainAspectRatio", NoSpinbox=true))
	int ResolutionX = 1920;

	/**
	* Min: 64px, Max: 4320
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Current Camera Settings", meta=(NoSpinbox=true))
	int ResolutionY = 1080;

	/**
	* Clear color of the render target
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Current Camera Settings")
	FLinearColor ClearColor = FLinearColor::Transparent;

	/**
	* Render Target Gamma
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Current Camera Settings")
	float TargetGamma = 2.2f;

	/** Tick if you want to pause rendering to the render target */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Current Camera Settings")
	bool PauseRendering = false;

	/** Tick if you want to render selected primitives only */
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Current Camera Settings")
	bool UseShowOnlyList = false;

	/** The components won't rendered by current component.*/
	UPROPERTY()
	TArray<TWeakObjectPtr<UPrimitiveComponent> > HiddenComponents;

	/** The actors to hide in the scene capture. */
	UPROPERTY(EditInstanceOnly, Category = "Current Camera Settings")
	TArray<AActor*> HiddenActors;

	/** The only components to be rendered by this scene capture, if PrimitiveRenderMode is set to UseShowOnlyList. */
	UPROPERTY()
	TArray<TWeakObjectPtr<UPrimitiveComponent> > ShowOnlyComponents;

	/** The only actors to be rendered by this scene capture, if PrimitiveRenderMode is set to UseShowOnlyList.*/
	UPROPERTY(EditInstanceOnly, Category = "Current Camera Settings")
	TArray<AActor*> ShowOnlyActors;

	/** Scales the distance used by LOD. Set to values greater than 1 to cause the scene capture to use lower LODs than the main view to speed up the scene capture pass. */
	UPROPERTY(EditAnywhere, Category = "Current Camera Settings", meta = (UIMin = ".1", UIMax = "10"), AdvancedDisplay)
	float LODDistanceFactor = 1.0f;

	/** if > 0, sets a maximum render distance override.  Can be used to cull distant objects from a reflection if the reflecting plane is in an enclosed area like a hallway or room */
	UPROPERTY(EditAnywhere, Category = "Current Camera Settings", meta = (UIMin = "100", UIMax = "10000"))
	float MaxViewDistanceOverride = -1;

	/* Toggles Temporal AntiAliasing */
	UPROPERTY(interp, EditAnywhere, Category = PostProcess)
	bool TemporalAAEnabled = true;

	/* Toggles Temporal AntiAliasing Motion BLur */
	UPROPERTY(interp, EditAnywhere, Category = PostProcess)
	bool TAAMotionBlurEnabled = true;

	/* Only works if Temporal AA enabled otherwise uses spatial upsamplng */
	UPROPERTY(interp, EditAnywhere, Category = PostProcess)
	bool TemporalAAUpsampling = true;

public:

	/** Adds the component to our list of hidden components. */
	UFUNCTION(BlueprintCallable, Category = "Rendering|SceneCapture")
	void HideComponent(UPrimitiveComponent* InComponent);

	/**
	 * Adds all primitive components in the actor to our list of hidden components.
	 * @param bIncludeFromChildActors Whether to include the components from child actors
	 */
	UFUNCTION(BlueprintCallable, Category = "Rendering|SceneCapture")
	void HideActorComponents(AActor* InActor, const bool bIncludeFromChildActors = false);

	/** Adds the component to our list of show-only components. */
	UFUNCTION(BlueprintCallable, Category = "Rendering|SceneCapture")
	void ShowOnlyComponent(UPrimitiveComponent* InComponent);

	/**
	* Adds all primitive components in the actor to our list of show-only components.
	* @param bIncludeFromChildActors Whether to include the components from child actors
	*/
	UFUNCTION(BlueprintCallable, Category = "Rendering|SceneCapture")
	void ShowOnlyActorComponents(AActor* InActor, const bool bIncludeFromChildActors = false);

	/** Removes a component from the Show Only list. */
	UFUNCTION(BlueprintCallable, Category = "Rendering|SceneCapture")
	void RemoveShowOnlyComponent(UPrimitiveComponent* InComponent);

	/**
	* Removes an actor's components from the Show Only list.
	* @param bIncludeFromChildActors Whether to remove the components from child actors
	*/
	UFUNCTION(BlueprintCallable, Category = "Rendering|SceneCapture")
	void RemoveShowOnlyActorComponents(AActor* InActor, const bool bIncludeFromChildActors = false);

	/** Clears the Show Only list. */
	UFUNCTION(BlueprintCallable, Category = "Rendering|SceneCapture")
	void ClearShowOnlyComponents();

	/** Clears the hidden list. */
	UFUNCTION(BlueprintCallable, Category = "Rendering|SceneCapture")
	void ClearHiddenComponents();

public:
	DECLARE_MULTICAST_DELEGATE(FOnRenderFinished);
	FOnRenderFinished OnRenderFinished;

	FSceneViewStateInterface* GetViewState(int32 ViewIndex);
	static void AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector);

	virtual void BeginDestroy() override;
	virtual void OnRegister() override;

protected:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void RenderScene();
	void SetupViewFamily(class FSceneViewFamily& ViewFamily, const TArrayView<FMinimalViewInfo> Views);
	void ResizeRenderTargetToMatchResolution(UTextureRenderTarget2D* RenderTarget);
	void SetupTextureTarget();
	void SetupInternalRT(const EPixelFormat PixelFormat);
	bool ShouldExit();

	/**
	 * The view state holds persistent scene rendering state and enables occlusion culling in scene captures.
	 * NOTE: This object is used by the rendering thread. When the game thread attempts to destroy it, FDeferredCleanupInterface will keep the object around until the RT is done accessing it.
	 * NOTE: It is not safe to put a FSceneViewStateReference in a TArray, which moves its contents around without calling element constructors during realloc.
	 */
	TIndirectArray<FSceneViewStateReference> ViewStates;
	float CurrentAspectRatio = 1.0f;
	UTextureRenderTarget2D* InternalRT = nullptr;

private:
	static FOWLAPIConfiguration APIConfig;

	int MaxResolutionX = 7680;
	int MaxResolutionY = 4320;
	int MinResolution = 64;
};