#include "ModularPlayerController.h"

#include <Components/ControllerComponent.h>
#include <Components/GameFrameworkComponentManager.h>

void AModularPlayerController::PreInitializeComponents()
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

void AModularPlayerController::EndPlay( const EEndPlayReason::Type EndPlayReason )
{
    if ( auto * system = GetGameInstance()->GetSubsystem< UGameFrameworkComponentManager >() )
    {
        system->RemoveReceiver( this );
    }

    Super::EndPlay( EndPlayReason );
}

void AModularPlayerController::ReceivedPlayer()
{
    // Player controllers always get assigned a player and can't do much until then
    // UE5 specific
    // UGameFrameworkComponentManager::SendGameFrameworkComponentExtensionEvent(this, UGameFrameworkComponentManager::NAME_GameActorReady);

    Super::ReceivedPlayer();

    TInlineComponentArray< UControllerComponent * > ModularComponents( this );
    for ( UControllerComponent * Component : ModularComponents )
    {
        Component->ReceivedPlayer();
    }
}

void AModularPlayerController::PlayerTick( float DeltaTime )
{
    Super::PlayerTick( DeltaTime );

    TInlineComponentArray< UControllerComponent * > ModularComponents( this );
    for ( UControllerComponent * Component : ModularComponents )
    {
        Component->PlayerTick( DeltaTime );
    }
}