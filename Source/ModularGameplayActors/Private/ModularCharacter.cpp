#include "ModularCharacter.h"

#include "ModularPawnComponent.h"
#include "Components/GameFrameworkComponentManager.h"

void AModularCharacter::PreInitializeComponents()
{
    Super::PreInitializeComponents();

    UGameFrameworkComponentManager::AddGameFrameworkComponentReceiver( this );
}

void AModularCharacter::BeginPlay()
{
    UGameFrameworkComponentManager::SendGameFrameworkComponentExtensionEvent( this, UGameFrameworkComponentManager::NAME_GameActorReady );

    Super::BeginPlay();
}

void AModularCharacter::EndPlay( const EEndPlayReason::Type EndPlayReason )
{
    UGameFrameworkComponentManager::RemoveGameFrameworkComponentReceiver( this );

    Super::EndPlay( EndPlayReason );
}

void AModularCharacter::UnPossessed()
{
    for (TComponentIterator< UModularPawnComponent > iterator( this ); iterator; ++iterator)
    {
        iterator->OnUnPossessed();
    }

    Super::UnPossessed();
}

void AModularCharacter::PossessedBy( AController * new_controller )
{
    Super::PossessedBy( new_controller );

    for (TComponentIterator< UModularPawnComponent > iterator( this ); iterator; ++iterator)
    {
        iterator->OnPossessedBy( new_controller );
    }
}

void AModularCharacter::OnRep_Controller()
{
    Super::OnRep_Controller();

    for (TComponentIterator< UModularPawnComponent > iterator( this ); iterator; ++iterator)
    {
        iterator->OnRep_Controller();
    }
}

void AModularCharacter::OnRep_PlayerState()
{
    Super::OnRep_PlayerState();

    for (TComponentIterator< UModularPawnComponent > iterator( this ); iterator; ++iterator)
    {
        iterator->OnRep_PlayerState();
    }
}

void AModularCharacter::SetupPlayerInputComponent( UInputComponent * PlayerInputComponent )
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    for (TComponentIterator< UModularPawnComponent > iterator( this ); iterator; ++iterator)
    {
        iterator->SetupPlayerInputComponent( PlayerInputComponent );
    }
}