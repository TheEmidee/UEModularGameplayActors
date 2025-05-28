#pragma once

#include <Components/ControllerComponent.h>
#include <CoreMinimal.h>

#include "ModularPlayerControllerComponent.generated.h"

UCLASS()
class MODULARGAMEPLAYACTORS_API UModularPlayerControllerComponent : public UControllerComponent
{
    GENERATED_BODY()

public:
    explicit UModularPlayerControllerComponent( const FObjectInitializer & object_initializer );

    virtual void OnPossess( APawn * pawn );
    virtual void OnUnPossess();
};
