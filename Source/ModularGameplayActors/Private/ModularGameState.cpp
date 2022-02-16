#include "ModularGameState.h"

#include <Components/GameFrameworkComponentManager.h>
#include <Components/GameStateComponent.h>

void AModularGameStateBase::PreInitializeComponents()
{
    Super::PreInitializeComponents();

    if ( auto * gi = GetGameInstance() )
    {
        if ( auto * system = gi->GetSubsystem< UGameFrameworkComponentManager >() )
        {
            system->AddReceiver( this );
        }
    }
}

void AModularGameStateBase::BeginPlay()
{
    // UE5 specific
    // UGameFrameworkComponentManager::SendGameFrameworkComponentExtensionEvent(this, UGameFrameworkComponentManager::NAME_GameActorReady);

    Super::BeginPlay();
}

void AModularGameStateBase::EndPlay( const EEndPlayReason::Type EndPlayReason )
{
    if ( auto * system = GetGameInstance()->GetSubsystem< UGameFrameworkComponentManager >() )
    {
        system->RemoveReceiver( this );
    }

    Super::EndPlay( EndPlayReason );
}

void AModularGameState::PreInitializeComponents()
{
    Super::PreInitializeComponents();

    if ( auto * gi = GetGameInstance() )
    {
        if ( auto * system = gi->GetSubsystem< UGameFrameworkComponentManager >() )
        {
            system->AddReceiver( this );
        }
    }
}

void AModularGameState::BeginPlay()
{
    // UE5 specific
    // UGameFrameworkComponentManager::SendGameFrameworkComponentExtensionEvent(this, UGameFrameworkComponentManager::NAME_GameActorReady);

    Super::BeginPlay();
}

void AModularGameState::EndPlay( const EEndPlayReason::Type EndPlayReason )
{
    if ( auto * system = GetGameInstance()->GetSubsystem< UGameFrameworkComponentManager >() )
    {
        system->RemoveReceiver( this );
    }

    Super::EndPlay( EndPlayReason );
}

void AModularGameState::HandleMatchHasStarted()
{
    Super::HandleMatchHasStarted();

    TArray< UGameStateComponent * > ModularComponents;
    GetComponents( ModularComponents );
    for ( UGameStateComponent * Component : ModularComponents )
    {
        Component->HandleMatchHasStarted();
    }
}
