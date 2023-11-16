// Copyright Epic Games, Inc. All Rights Reserved.

#include "ModularPawn.h"
#include "Components/GameFrameworkComponentManager.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ModularPawn)

void AModularPawn::PreInitializeComponents()
{
	Super::PreInitializeComponents();

	UGameFrameworkComponentManager::AddGameFrameworkComponentReceiver(this);
}

void AModularPawn::BeginPlay()
{
	UGameFrameworkComponentManager::SendGameFrameworkComponentExtensionEvent(this, UGameFrameworkComponentManager::NAME_GameActorReady);

	Super::BeginPlay();
}

void AModularPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UGameFrameworkComponentManager::RemoveGameFrameworkComponentReceiver(this);

	Super::EndPlay(EndPlayReason);
}

void AModularPawn::UnPossessed()
{
    for ( TComponentIterator< UModularPawnComponent > iterator( this ); iterator; ++iterator )
    {
        iterator->OnUnPossessed();
    }

    Super::UnPossessed();
}

void AModularPawn::PossessedBy( AController * new_controller )
{
    Super::PossessedBy( new_controller );

    for ( TComponentIterator< UModularPawnComponent > iterator( this ); iterator; ++iterator )
    {
        iterator->OnPossessedBy( new_controller );
    }
}
