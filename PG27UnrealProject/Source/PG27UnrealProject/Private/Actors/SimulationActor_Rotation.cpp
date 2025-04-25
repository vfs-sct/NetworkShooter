// VFS Rohit 2025-2026


#include "Actors/SimulationActor_Rotation.h"
#include "GameFramework/RotatingMovementComponent.h"

ASimulationActor_Rotation::ASimulationActor_Rotation()
{
	RotatingComponent = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("Rotating Comp"));


	RotatingComponent->SetUpdatedComponent(RootComponent);
}
