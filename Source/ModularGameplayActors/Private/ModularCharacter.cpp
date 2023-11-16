// Copyright Epic Games, Inc. All Rights Reserved.

#include "ModularCharacter.h"

#include "ModularPawnComponent.h"
#include "Components/GameFrameworkComponentManager.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ModularCharacter)

void AModularCharacter::PreInitializeComponents()
{
	Super::PreInitializeComponents();

	UGameFrameworkComponentManager::AddGameFrameworkComponentReceiver(this);
}

void AModularCharacter::BeginPlay()
{
	UGameFrameworkComponentManager::SendGameFrameworkComponentExtensionEvent(this, UGameFrameworkComponentManager::NAME_GameActorReady);

	Super::BeginPlay();
}

void AModularCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UGameFrameworkComponentManager::RemoveGameFrameworkComponentReceiver(this);

	Super::EndPlay(EndPlayReason);
}

void AModularCharacter::UnPossessed()
{
    for ( TComponentIterator< UModularPawnComponent > iterator( this ); iterator; ++iterator )
    {
        iterator->OnUnPossessed();
    }

    Super::UnPossessed();
}

void AModularCharacter::PossessedBy( AController * new_controller )
{
    Super::PossessedBy( new_controller );

    for ( TComponentIterator< UModularPawnComponent > iterator( this ); iterator; ++iterator )
    {
        iterator->OnPossessedBy( new_controller );
    }
}