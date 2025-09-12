#include "ModularPawnComponent.h"

#include "ModularGameplayTags.h"

UModularPawnComponent::UModularPawnComponent( const FObjectInitializer & ObjectInitializer ) :
    Super( ObjectInitializer )
{
}

void UModularPawnComponent::CheckDefaultInitialization()
{
    static const TArray< FGameplayTag > StateChain = { ModularGameplayTag_InitState_Spawned, ModularGameplayTag_InitState_DataAvailable, ModularGameplayTag_InitState_DataInitialized, ModularGameplayTag_InitState_GameplayReady };

    // This will try to progress from spawned (which is only set in BeginPlay) through the data initialization stages until it gets to gameplay ready
    ContinueInitStateChain( StateChain );
}

void UModularPawnComponent::OnPossessedBy( AController * /*NewController*/ )
{
    CheckDefaultInitialization();
}

void UModularPawnComponent::OnUnPossessed()
{
    CheckDefaultInitialization();
}

void UModularPawnComponent::OnRep_Controller()
{
    CheckDefaultInitialization();
}

void UModularPawnComponent::OnRep_PlayerState()
{
    CheckDefaultInitialization();
}

void UModularPawnComponent::SetupPlayerInputComponent( UInputComponent * PlayerInputComponent )
{
    CheckDefaultInitialization();
}

void UModularPawnComponent::OnRegister()
{
    Super::OnRegister();

    // Register with the init state system early, this will only work if this is a game world
    RegisterInitStateFeature();
}

void UModularPawnComponent::BeginPlay()
{
    Super::BeginPlay();

    BindToRequiredOnActorInitStateChanged();

    // Notifies state manager that we have spawned, then try rest of default initialization
    ensureAlways( TryToChangeInitState( ModularGameplayTag_InitState_Spawned ) );
    CheckDefaultInitialization();
}

void UModularPawnComponent::EndPlay( const EEndPlayReason::Type EndPlayReason )
{
    UnregisterInitStateFeature();

    Super::EndPlay( EndPlayReason );
}

void UModularPawnComponent::BindToRequiredOnActorInitStateChanged()
{
}