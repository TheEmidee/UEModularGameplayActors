#include "ModularPlayerControllerComponent.h"

#include "ModularGameplayTags.h"

UModularPlayerControllerComponent::UModularPlayerControllerComponent( const FObjectInitializer & ObjectInitializer ) :
    Super( ObjectInitializer )
{
}

void UModularPlayerControllerComponent::CheckDefaultInitialization()
{
    static const TArray< FGameplayTag > StateChain = { ModularGameplayTag_InitState_Spawned, ModularGameplayTag_InitState_DataAvailable, ModularGameplayTag_InitState_DataInitialized, ModularGameplayTag_InitState_GameplayReady };

    // This will try to progress from spawned (which is only set in BeginPlay) through the data initialization stages until it gets to gameplay ready
    ContinueInitStateChain( StateChain );
}

void UModularPlayerControllerComponent::OnPossess( APawn * pawn )
{
    CheckDefaultInitialization();
}

void UModularPlayerControllerComponent::OnUnPossess()
{
    CheckDefaultInitialization();
}

void UModularPlayerControllerComponent::OnRegister()
{
    Super::OnRegister();

    // Register with the init state system early, this will only work if this is a game world
    RegisterInitStateFeature();
}

void UModularPlayerControllerComponent::BeginPlay()
{
    Super::BeginPlay();

    BindToRequiredOnActorInitStateChanged();

    // Notifies state manager that we have spawned, then try rest of default initialization
    ensureAlways( TryToChangeInitState( ModularGameplayTag_InitState_Spawned ) );
    CheckDefaultInitialization();
}

void UModularPlayerControllerComponent::EndPlay( const EEndPlayReason::Type end_play_reason )
{
    UnregisterInitStateFeature();

    Super::EndPlay( end_play_reason );
}

void UModularPlayerControllerComponent::BindToRequiredOnActorInitStateChanged()
{
}