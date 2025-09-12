#include "ModularPawnOrchestratorComponent.h"

#include "ModularGameplayTags.h"
#include "Components/GameFrameworkComponentManager.h"
#include "GameFramework/Controller.h"
#include "Net/UnrealNetwork.h"

const FName UModularPawnOrchestratorComponent::NAME_ActorFeatureName( "ModularPawnOrchestratorComponent" );

UModularPawnOrchestratorComponent::UModularPawnOrchestratorComponent( const FObjectInitializer & ObjectInitializer ) :
    Super( ObjectInitializer )
{
    PrimaryComponentTick.bStartWithTickEnabled = false;
    PrimaryComponentTick.bCanEverTick = false;

    SetIsReplicatedByDefault( true );
}

void UModularPawnOrchestratorComponent::OnPawnReadyToInitialize_UnRegister( const FSimpleMulticastDelegate::FDelegate & Delegate )
{
    OnPawnReadyToInitialize.Remove( Delegate.GetHandle() );
}

FName UModularPawnOrchestratorComponent::GetFeatureName() const
{
    return NAME_ActorFeatureName;
}

void UModularPawnOrchestratorComponent::CheckDefaultInitialization()
{
    // Before checking our progress, try progressing any other features we might depend on
    CheckDefaultInitializationForImplementers();

    Super::CheckDefaultInitialization();
}

bool UModularPawnOrchestratorComponent::CanChangeInitState( UGameFrameworkComponentManager * Manager, FGameplayTag CurrentState, FGameplayTag DesiredState ) const
{
    check( Manager != nullptr );

    auto * Pawn = GetPawn< APawn >();

    if (!CurrentState.IsValid() && DesiredState == ModularGameplayTag_InitState_Spawned)
    {
        return Pawn != nullptr;
    }
    if (CurrentState == ModularGameplayTag_InitState_Spawned && DesiredState == ModularGameplayTag_InitState_DataAvailable)
    {
        const auto bHasAuthority = Pawn->HasAuthority();
        const auto bIsLocallyControlled = Pawn->IsLocallyControlled();

        if (bHasAuthority || bIsLocallyControlled)
        {
            // Check for being possessed by a controller.
            if (GetController< AController >() == nullptr)
            {
                return false;
            }
        }

        return true;
    }
    if (CurrentState == ModularGameplayTag_InitState_DataAvailable && DesiredState == ModularGameplayTag_InitState_DataInitialized)
    {
        // Transition to initialize if all features have their data available
        return Manager->HaveAllFeaturesReachedInitState( Pawn, ModularGameplayTag_InitState_DataAvailable );
    }
    if (CurrentState == ModularGameplayTag_InitState_DataInitialized && DesiredState == ModularGameplayTag_InitState_GameplayReady)
    {
        return true;
    }

    return false;
}

void UModularPawnOrchestratorComponent::HandleChangeInitState( UGameFrameworkComponentManager * Manager, FGameplayTag CurrentState, FGameplayTag DesiredState )
{
    // This is currently all handled by other components listening to this state change
}

void UModularPawnOrchestratorComponent::OnActorInitStateChanged( const FActorInitStateChangedParams & Params )
{
    // If another feature is now in DataAvailable, see if we should transition to DataInitialized
    if (Params.FeatureName != NAME_ActorFeatureName)
    {
        if (Params.FeatureState == ModularGameplayTag_InitState_DataAvailable)
        {
            CheckDefaultInitialization();
        }
    }
}

UModularPawnOrchestratorComponent * UModularPawnOrchestratorComponent::FindPawnOrchestratorComponent( const AActor * Actor )
{
    return Actor
               ? Actor->FindComponentByClass< UModularPawnOrchestratorComponent >()
               : nullptr;
}

void UModularPawnOrchestratorComponent::OnRegister()
{
    Super::OnRegister();

    const auto * Pawn = GetPawn< APawn >();
    if (!ensureAlwaysMsgf( ( Pawn != nullptr ), TEXT( "ModularPawnOrchestratorComponent on [%s] can only be added to Pawn actors." ), *GetNameSafe( GetOwner() ) ))
    {
        return;
    }

    TArray< UActorComponent * > PawnExtensionComponents;
    Pawn->GetComponents( StaticClass(), PawnExtensionComponents );
    ensureAlwaysMsgf( ( PawnExtensionComponents.Num() == 1 ), TEXT( "Only one ModularPawnOrchestratorComponent should exist on [%s]." ), *GetNameSafe( GetOwner() ) );
}

void UModularPawnOrchestratorComponent::BindToRequiredOnActorInitStateChanged()
{
    // Listen for changes to all features
    BindOnActorInitStateChanged( NAME_None, FGameplayTag(), false );
}