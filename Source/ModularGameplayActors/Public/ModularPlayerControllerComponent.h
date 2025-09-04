#pragma once

#include "Components/GameFrameworkInitStateInterface.h"
#include "Components/ControllerComponent.h"
#include "CoreMinimal.h"

#include "ModularPlayerControllerComponent.generated.h"

UCLASS()
class MODULARGAMEPLAYACTORS_API UModularPlayerControllerComponent : public UControllerComponent, public IGameFrameworkInitStateInterface
{
    GENERATED_BODY()

public:
    explicit UModularPlayerControllerComponent( const FObjectInitializer & ObjectInitializer );

    void CheckDefaultInitialization() override;

    virtual void OnPossess( APawn * Pawn );
    virtual void OnUnPossess();

protected:
    void OnRegister() override;
    void BeginPlay() override;
    void EndPlay( const EEndPlayReason::Type end_play_reason ) override;
    virtual void BindToRequiredOnActorInitStateChanged();
};