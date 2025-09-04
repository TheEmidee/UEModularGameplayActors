#pragma once

#include "Components/GameFrameworkInitStateInterface.h"
#include "Components/PawnComponent.h"
#include "CoreMinimal.h"

#include "ModularPawnComponent.generated.h"

UCLASS()
class MODULARGAMEPLAYACTORS_API UModularPawnComponent : public UPawnComponent, public IGameFrameworkInitStateInterface
{
    GENERATED_BODY()

public:
    explicit UModularPawnComponent( const FObjectInitializer & ObjectInitializer );

    void CheckDefaultInitialization() override;

    virtual void OnPossessedBy( AController * NewController );
    virtual void OnUnPossessed();
    virtual void OnRep_Controller();
    virtual void OnRep_PlayerState();
    virtual void SetupPlayerInputComponent( UInputComponent * PlayerInputComponent );

protected:
    void OnRegister() override;
    void BeginPlay() override;
    void EndPlay( const EEndPlayReason::Type EndPlayReason ) override;
    virtual void BindToRequiredOnActorInitStateChanged();
};