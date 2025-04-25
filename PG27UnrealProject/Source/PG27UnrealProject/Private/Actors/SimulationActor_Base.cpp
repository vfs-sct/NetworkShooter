// VFS Rohit 2025-2026


#include "Actors/SimulationActor_Base.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
ASimulationActor_Base::ASimulationActor_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body Mesh"));
	SetRootComponent(Body);
}

// Called when the game starts or when spawned
void ASimulationActor_Base::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASimulationActor_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

