// Copyright Epic Games, Inc. All Rights Reserved.

#include "ModularPlayerController.h"

#include "ModularPlayerControllerComponent.h"
#include "Components/ControllerComponent.h"
#include "Components/GameFrameworkComponentManager.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ModularPlayerController)

void AModularPlayerController::PreInitializeComponents()
{
	Super::PreInitializeComponents();

	UGameFrameworkComponentManager::AddGameFrameworkComponentReceiver(this);
}

void AModularPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UGameFrameworkComponentManager::RemoveGameFrameworkComponentReceiver(this);

	Super::EndPlay(EndPlayReason);
}

void AModularPlayerController::ReceivedPlayer()
{
	// Player controllers always get assigned a player and can't do much until then
	UGameFrameworkComponentManager::SendGameFrameworkComponentExtensionEvent(this, UGameFrameworkComponentManager::NAME_GameActorReady);

	Super::ReceivedPlayer();

	TArray< UModularPlayerControllerComponent * > ModularComponents;
	GetComponents(ModularComponents);
    for ( UModularPlayerControllerComponent * Component : ModularComponents )
	{
		Component->ReceivedPlayer();
	}
}

void AModularPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	TArray< UModularPlayerControllerComponent * > ModularComponents;
	GetComponents(ModularComponents);
    for ( UModularPlayerControllerComponent * Component : ModularComponents )
	{
		Component->PlayerTick(DeltaTime);
	}
}

void AModularPlayerController::OnPossess( APawn * aPawn )
{
    Super::OnPossess( aPawn );

	TArray< UModularPlayerControllerComponent * > ModularComponents;
    GetComponents( ModularComponents );
    for ( UModularPlayerControllerComponent * Component : ModularComponents )
    {
        Component->OnPossess( aPawn );
    }
}

void AModularPlayerController::OnUnPossess()
{
    Super::OnUnPossess();

    TArray< UModularPlayerControllerComponent * > ModularComponents;
    GetComponents( ModularComponents );
    for ( UModularPlayerControllerComponent * Component : ModularComponents )
    {
        Component->OnUnPossess();
    }
}
