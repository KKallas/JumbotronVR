// Copyright Off World Live Limited, 2020-2021. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Tickable.h"
#include "OWLSpoutReceiverManager.generated.h"


USTRUCT(BlueprintType)
struct FOWLSpoutReceiver
{
	GENERATED_BODY()

public:
	FOWLSpoutReceiver()
		: Active(0), 
		Name(FString()), 
		RenderTarget(nullptr)
	{ }

	FOWLSpoutReceiver(
		bool InitActive, 
		FString InitName,
		UTextureRenderTarget2D* InitTextureTarget)
		: Active(InitActive), 
		Name(InitName), 
		RenderTarget(InitTextureTarget)
	{ }

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = OWLSpoutReceiver)
	bool Active;

	/* Name of the sender we are receiving from */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = OWLSpoutReceiver)
	FString Name = FString::FString("");

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = OWLSpoutReceiver)
	UTextureRenderTarget2D* RenderTarget;

	FString NameRegistered = FString();
};

struct FReceiverTickHelper : FTickableGameObject
{
	TWeakObjectPtr<class AOWLSpoutReceiverManager> Owner;

	FReceiverTickHelper() : Owner(NULL) {}
	virtual void Tick(float DeltaTime);
	virtual bool IsTickable() const { return Owner.IsValid(); }
	virtual bool IsTickableInEditor() const { return true; }
	virtual bool IsTickableWhenPaused() const override { return true; }
	virtual TStatId GetStatId() const;
};

UCLASS()
class LIVESTREAMINGTOOLKIT_API AOWLSpoutReceiverManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AOWLSpoutReceiverManager(const FObjectInitializer& ObjectInitializer);

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif // WITH_EDITOR

	FDelegateHandle OnLevelActorDeletedHandle;
	void OnLevelActorDeleted(AActor* DestroyedActor);

public:
	virtual void TickMe(float DeltaTime);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Off World Live Spout Sender Settings")
	TArray<FOWLSpoutReceiver> SpoutReceivers;

protected:
	virtual void BeginDestroy() override;
	virtual void PostInitProperties() override;

private:

	UPROPERTY(Category = Components, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* SceneComponent;

	TArray<FString> RegisteredNames;
	FReceiverTickHelper TickHelper;
};
