#pragma once

#include "CoreMinimal.h"
#include "ModularPawnComponent.h"
#include "ModularPawnOrchestratorComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGEDynamicMulticastDelegate);

UCLASS()
class MODULARGAMEPLAYACTORS_API UModularPawnOrchestratorComponent : public UModularPawnComponent
{
    GENERATED_BODY()

public:
    explicit UModularPawnOrchestratorComponent(const FObjectInitializer & ObjectInitializer);

    // UnRegister with the OnPawnReadyToInitialize delegate.
    void OnPawnReadyToInitialize_UnRegister(const FSimpleMulticastDelegate::FDelegate& Delegate);

    FName GetFeatureName() const override;
    void CheckDefaultInitialization() override;
    bool CanChangeInitState(UGameFrameworkComponentManager* Manager, FGameplayTag CurrentState, FGameplayTag DesiredState) const override;
    void HandleChangeInitState(UGameFrameworkComponentManager* Manager, FGameplayTag CurrentState, FGameplayTag DesiredState) override;
    void OnActorInitStateChanged(const FActorInitStateChangedParams& Params) override;
    
    UFUNCTION(BlueprintPure, Category = "ModularGameplayActors|Pawn|Components")
    static UModularPawnOrchestratorComponent* FindPawnOrchestratorComponent(const AActor* Actor);

    /** The name of this overall feature, this one depends on the other named component features */
    static const FName NAME_ActorFeatureName;

protected:
    void OnRegister() override;
    void BindToRequiredOnActorInitStateChanged() override;

    FSimpleMulticastDelegate OnPawnReadyToInitialize;

    UPROPERTY(BlueprintAssignable, Meta = ( DisplayName = "On Pawn Ready To Initialize" ))
    FGEDynamicMulticastDelegate BP_OnPawnReadyToInitialize;
};