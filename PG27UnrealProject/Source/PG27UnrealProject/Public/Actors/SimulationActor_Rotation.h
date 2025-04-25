// VFS Rohit 2025-2026

#pragma once

#include "CoreMinimal.h"
#include "Actors/SimulationActor_Base.h"
#include "SimulationActor_Rotation.generated.h"

/**
 * 
 */
class URotatingMovementComponent;

UCLASS()
class PG27UNREALPROJECT_API ASimulationActor_Rotation : public ASimulationActor_Base
{
	GENERATED_BODY()

public:

	ASimulationActor_Rotation();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<URotatingMovementComponent> RotatingComponent;
	
};
