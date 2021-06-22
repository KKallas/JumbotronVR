// Copyright Off World Live Limited, 2020-2021. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CineCameraActor.h"
#include "OWLCineCamCapture.generated.h"

UCLASS(hidecategories = (Collision, Attachment, Actor))
class LIVESTREAMINGTOOLKIT_API AOWLCineCamCapture : public AActor
{
	GENERATED_BODY()

public:
	AOWLCineCamCapture(const FObjectInitializer& ObjectInitializer);

private:
	UPROPERTY(Category = Components, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* SceneComponent;

	UPROPERTY(Category = DecalActor, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UOWLCineCamCaptureComponent* CineCamCaptureComponent = nullptr;

protected:
	/** Set to true to skip any interpolations on the next update. Resets to false automatically. */
	uint8 bResetInterplation : 1;

	FVector GetLookatLocation() const;
	virtual bool ShouldTickIfViewportsOnly() const override;
	bool ShouldTickForTracking() const;

public:
	UFUNCTION(BlueprintCallable, Category = "Rendering")
	void OnInterpToggle(bool bEnable);

	virtual void CalcCamera(float DeltaTime, struct FMinimalViewInfo& OutMinimalViewInfo) override;

	/** Returns CaptureComponent2D subobject **/
	class UOWLCineCamCaptureComponent* GetCineCamCaptureComponent() const { return CineCamCaptureComponent; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Current Camera Settings")
	FCameraLookatTrackingSettings LookatTrackingSettings;

	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;
};