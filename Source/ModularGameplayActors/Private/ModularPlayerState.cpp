// Copyright Epic Games, Inc. All Rights Reserved.

#include "ModularPlayerState.h"
#include "Components/GameFrameworkComponentManager.h"
#include "Components/PlayerStateComponent.h"

void AModularPlayerState::PreInitializeComponents()
{
	Super::PreInitializeComponents();

	UGameFrameworkComponentManager::AddGameFrameworkComponentReceiver(this);
}

void AModularPlayerState::BeginPlay()
{
	UGameFrameworkComponentManager::SendGameFrameworkComponentExtensionEvent(this, UGameFrameworkComponentManager::NAME_GameActorReady);

	Super::BeginPlay();
}

void AModularPlayerState::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UGameFrameworkComponentManager::RemoveGameFrameworkComponentReceiver(this);

	Super::EndPlay(EndPlayReason);
}

void AModularPlayerState::Reset()
{
	Super::Reset();

	TArray<UPlayerStateComponent*> ModularComponents;
	GetComponents(ModularComponents);
	for (UPlayerStateComponent* Component : ModularComponents)
	{
		Component->Reset();
	}
}

void AModularPlayerState::CopyProperties(APlayerState* PlayerState)
{
	Super::Reset();

	TArray<UPlayerStateComponent*> ModularComponents;
	GetComponents(ModularComponents);

	TArray<UPlayerStateComponent*> OtherModularComponents;
	PlayerState->GetComponents(OtherModularComponents);

	for (UPlayerStateComponent* Component : ModularComponents)
	{
		for (UPlayerStateComponent* OtherComponent : OtherModularComponents)
		{
			Component->CopyProperties(OtherComponent);
		}
	}
}