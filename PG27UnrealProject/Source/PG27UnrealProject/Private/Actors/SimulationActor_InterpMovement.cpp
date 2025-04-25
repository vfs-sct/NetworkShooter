// VFS Rohit 2025-2026


#include "Actors/SimulationActor_InterpMovement.h"
#include "Components/InterpToMovementComponent.h"

ASimulationActor_InterpMovement::ASimulationActor_InterpMovement()
{
	InterpMovementComp = CreateDefaultSubobject<UInterpToMovementComponent>(TEXT("Interp Movement Comp"));
	InterpMovementComp->SetUpdatedComponent(RootComponent);
	UpdateInterpMovementCompValues();
}

void ASimulationActor_InterpMovement::BeginPlay()
{
	Super::BeginPlay();

	UpdateInterpMovementCompValues();
}

void ASimulationActor_InterpMovement::UpdateInterpMovementCompValues()
{
	for (const FVector& Position : InterpPoints)
	{
		if (InterpMovementComp)
		{
			InterpMovementComp->AddControlPointPosition(Position);
		}
	}
	InterpMovementComp->FinaliseControlPoints();
}
