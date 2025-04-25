// VFS Rohit 2025-2026


#include "Actors/ItemBase.h"

// Sets default values
AItemBase::AItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bNetLoadOnClient = true;
	SetReplicates(true);
	bReplicates = true;
}

void AItemBase::UseItem_SER_Implementation()
{
	BP_OnUseItem();
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "On Item Used");
	}
}

void AItemBase::BP_OnUseItem_Implementation()
{
	OnItemUsed.Broadcast();
}

// Called when the game starts or when spawned
void AItemBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

