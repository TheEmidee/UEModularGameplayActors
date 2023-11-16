// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "GameFramework/GameMode.h"

#include "ModularGameMode.generated.h"

class UObject;

/** Pair this with a ModularGameStateBase */
UCLASS(Blueprintable)
class MODULARGAMEPLAYACTORS_API AModularGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AModularGameModeBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void PreInitializeComponents() override;

protected:
    virtual void BeginPlay() override;
    virtual void EndPlay( const EEndPlayReason::Type EndPlayReason ) override;
};

/** Pair this with a ModularGameState */
UCLASS(Blueprintable)
class MODULARGAMEPLAYACTORS_API AModularGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AModularGameMode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual bool ReadyToStartMatch_Implementation() override;
    virtual void PreInitializeComponents() override;
    virtual void InitGameState() override;

protected:
    virtual void BeginPlay() override;
    virtual void EndPlay( const EEndPlayReason::Type EndPlayReason ) override;
    virtual void HandleMatchHasStarted() override;
};
