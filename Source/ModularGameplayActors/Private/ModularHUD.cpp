#include "ModularHUD.h"

#include "Components/GameFrameworkComponentManager.h"

AModularHUD::AModularHUD( const FObjectInitializer & object_initializer ) :
    Super( object_initializer )
{
    PrimaryActorTick.bStartWithTickEnabled = false;
}

void AModularHUD::PreInitializeComponents()
{
    Super::PreInitializeComponents();

    UGameFrameworkComponentManager::AddGameFrameworkComponentReceiver( this );
}

void AModularHUD::BeginPlay()
{
    UGameFrameworkComponentManager::SendGameFrameworkComponentExtensionEvent( this, UGameFrameworkComponentManager::NAME_GameActorReady );

    Super::BeginPlay();
}

void AModularHUD::EndPlay( const EEndPlayReason::Type end_play_reason )
{
    UGameFrameworkComponentManager::RemoveGameFrameworkComponentReceiver( this );

    Super::EndPlay( end_play_reason );
}
