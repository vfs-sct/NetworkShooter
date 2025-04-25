// VFS Rohit 2025-2026

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SimulationActor_Base.generated.h"

class UStaticMeshComponent;

// UCLASS, UPROPERTY, UFUNCTION, USTRUCT, UDELEGATE
UCLASS(Abstract)
class PG27UNREALPROJECT_API ASimulationActor_Base : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASimulationActor_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Mesh")
	TObjectPtr<UStaticMeshComponent> Body = nullptr;

};
