// VFS Rohit 2025-2026

#pragma once

#include "CoreMinimal.h"
#include "Actors/SimulationActor_Base.h"
#include "SimulationActor_InterpMovement.generated.h"

/**
 * 
 */

class UInterpToMovementComponent;

UCLASS()
class PG27UNREALPROJECT_API ASimulationActor_InterpMovement : public ASimulationActor_Base
{
	GENERATED_BODY()

public:

	ASimulationActor_InterpMovement();

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UInterpToMovementComponent> InterpMovementComp;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MakeEditWidget))
	TArray<FVector> InterpPoints;

private:

	void UpdateInterpMovementCompValues();
};
