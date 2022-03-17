#include "ModularPawn.h"

#include "ModularPawnComponent.h"

#include <Components/GameFrameworkComponentManager.h>

void AModularPawn::PreInitializeComponents()
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

void AModularPawn::BeginPlay()
{
    // UE5 specific
    // UGameFrameworkComponentManager::SendGameFrameworkComponentExtensionEvent(this, UGameFrameworkComponentManager::NAME_GameActorReady);

    Super::BeginPlay();
}

void AModularPawn::EndPlay( const EEndPlayReason::Type EndPlayReason )
{
    if ( auto * system = GetGameInstance()->GetSubsystem< UGameFrameworkComponentManager >() )
    {
        system->RemoveReceiver( this );
    }

    Super::EndPlay( EndPlayReason );
}

void AModularPawn::UnPossessed()
{
    TInlineComponentArray< UModularPawnComponent * > components( this );
    for ( auto * component : components )
    {
        component->OnUnPossessed();
    }

    Super::UnPossessed();
}

void AModularPawn::PossessedBy( AController * new_controller )
{
    Super::PossessedBy( new_controller );

    TInlineComponentArray< UModularPawnComponent * > components( this );
    for ( auto * component : components )
    {
        component->OnPossessedBy( new_controller );
    }
}
