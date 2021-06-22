// Copyright Off World Live Limited, 2020-2021. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Tickable.h"
#include "OWLSpoutSenderManager.generated.h"



USTRUCT(BlueprintType)
struct FOWLSpoutSender
{
	GENERATED_BODY()

public:
	FOWLSpoutSender()
		: Active(0),
		Name(FString()), 
		StandaloneName(FString()),
		RenderTarget(nullptr)
	{ }

	FOWLSpoutSender(
		bool InitActive,
		FString InitName,
		FString InitStandaloneName,
		UTextureRenderTarget2D* InitRenderTarget)
		: Active(InitActive),
		Name(InitName), 
		StandaloneName(InitStandaloneName),
		RenderTarget(InitRenderTarget)
	{ }

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = OWLSpoutSender)
	bool Active;

	/* Spout sender name that is used in editor targets */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = OWLSpoutSender)
	FString Name;

	/* Spout sender name that is used in game (standalone/packaged) targets  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = OWLSpoutSender)
	FString StandaloneName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = OWLSpoutSender)
	UTextureRenderTarget2D* RenderTarget;

	FString NameRegistered = FString();
};

struct FSenderTickHelper : FTickableGameObject
{
	TWeakObjectPtr<class AOWLSpoutSenderManager> Owner;

	FSenderTickHelper() : Owner(NULL) {}
	virtual void Tick(float DeltaTime);
	virtual bool IsTickable() const { return Owner.IsValid(); }
	virtual bool IsTickableInEditor() const { return true; }
	virtual bool IsTickableWhenPaused() const override { return true; }
	virtual TStatId GetStatId() const;
};

UCLASS()
class LIVESTREAMINGTOOLKIT_API AOWLSpoutSenderManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AOWLSpoutSenderManager(const FObjectInitializer& ObjectInitializer);

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif // WITH_EDITOR

	FDelegateHandle OnLevelActorDeletedHandle;
	void OnLevelActorDeleted(AActor* DestroyedActor);

public:
	virtual void TickMe(float DeltaTime);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Off World Live Spout Sender Settings")
	TArray<FOWLSpoutSender> SpoutSenders;

protected:
	virtual void BeginDestroy() override;
	virtual void PostInitProperties() override;

private:

	TEnumAsByte<EWorldType::Type> StartingWorldType = EWorldType::None;

	void PushSpoutSenderData(FString Name, FOWLSpoutSender* Sender);
	void CloseSpoutSender(FOWLSpoutSender* Sender);

	void ValidateSender(FString Name, FOWLSpoutSender* Sender);

	void CloseSenderIfRegistered(FOWLSpoutSender* Sender);

	bool FirstTick = true;

	UPROPERTY(Category = Components, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* SceneComponent;

	TArray<FString> RegisteredNames;
	FSenderTickHelper TickHelper;
};
