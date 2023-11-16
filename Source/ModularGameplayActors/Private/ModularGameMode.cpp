// Copyright Epic Games, Inc. All Rights Reserved.

#include "ModularGameMode.h"

#include "ModularGameModeComponent.h"
#include "ModularGameState.h"
#include "ModularPawn.h"
#include "ModularPlayerController.h"
#include "ModularPlayerState.h"
#include "Components/GameFrameworkComponentManager.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ModularGameMode)

AModularGameModeBase::AModularGameModeBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	GameStateClass = AModularGameStateBase::StaticClass();
	PlayerControllerClass = AModularPlayerController::StaticClass();
	PlayerStateClass = AModularPlayerState::StaticClass();
	DefaultPawnClass = AModularPawn::StaticClass();
}

void AModularGameModeBase::PreInitializeComponents()
{
    Super::PreInitializeComponents();

    UGameFrameworkComponentManager::AddGameFrameworkComponentReceiver( this );
}

void AModularGameModeBase::BeginPlay()
{
    UGameFrameworkComponentManager::SendGameFrameworkComponentExtensionEvent( this, UGameFrameworkComponentManager::NAME_GameActorReady );

    Super::BeginPlay();
}

void AModularGameModeBase::EndPlay( const EEndPlayReason::Type EndPlayReason )
{
    UGameFrameworkComponentManager::RemoveGameFrameworkComponentReceiver( this );

    Super::EndPlay( EndPlayReason );
}

AModularGameMode::AModularGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	GameStateClass = AModularGameState::StaticClass();
	PlayerControllerClass = AModularPlayerController::StaticClass();
	PlayerStateClass = AModularPlayerState::StaticClass();
	DefaultPawnClass = AModularPawn::StaticClass();
}

bool AModularGameMode::ReadyToStartMatch_Implementation()
{
    TInlineComponentArray< UModularGameModeComponent * > flow_components( this );

    for ( const auto * component : flow_components )
    {
        if ( !component->IsReadyToStartMatch() )
        {
            return false;
        }
    }

    return Super::ReadyToStartMatch_Implementation();
}

void AModularGameMode::PreInitializeComponents()
{
    Super::PreInitializeComponents();

    UGameFrameworkComponentManager::AddGameFrameworkComponentReceiver( this );
}

void AModularGameMode::InitGameState()
{
    Super::InitGameState();

    for ( TComponentIterator< UModularGameModeComponent > iterator( this ); iterator; ++iterator )
    {
        iterator->OnInitGameState();
    }
}

void AModularGameMode::BeginPlay()
{
    UGameFrameworkComponentManager::SendGameFrameworkComponentExtensionEvent( this, UGameFrameworkComponentManager::NAME_GameActorReady );

    Super::BeginPlay();
}

void AModularGameMode::EndPlay( const EEndPlayReason::Type EndPlayReason )
{
    UGameFrameworkComponentManager::RemoveGameFrameworkComponentReceiver( this );

    Super::EndPlay( EndPlayReason );
}

void AModularGameMode::HandleMatchHasStarted()
{
    Super::HandleMatchHasStarted();

    for ( TComponentIterator< UModularGameModeComponent > iterator( this ); iterator; ++iterator )
    {
        iterator->HandleMatchHasStarted();
    }
}
