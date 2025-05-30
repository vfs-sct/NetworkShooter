// VFS Rohit 2025-2026


#include "Actors/ItemPickupBase.h"

#include "NetworkShooterCharacter.h"
#include "Components/ItemManagerComponentBase.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Data/ItemPickupData.h"
#include "GameFramework/PlayerState.h"
#include "../Public/Components/NetworkHealthComponent.h"
#include "Components/NetworkCurrencyComponent.h"

// Sets default values
AItemPickupBase::AItemPickupBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bNetLoadOnClient = true;
	SetReplicates(true);

	ItemMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMeshComponent"));
	RootComponent = ItemMeshComponent;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	CollisionComponent->SetupAttachment(ItemMeshComponent);
}

// Called when the game starts or when spawned
void AItemPickupBase::BeginPlay()
{
	Super::BeginPlay();

	if (PickupItemData && PickupItemData->PickupMesh)
	{
		ItemMeshComponent->SetStaticMesh(PickupItemData->PickupMesh);
		Price = PickupItemData->Price; // on begin play set the price of the item
	}
	if (HasAuthority())
	{
		CollisionComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &AItemPickupBase::OnItemCollisionBegin_SER);
	}
	
}

// when overlap check if the player has enough currency
// if player have enough currency pick up item
void AItemPickupBase::OnItemCollisionBegin_SER_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ANetworkShooterCharacter* ShooterCharacter = Cast<ANetworkShooterCharacter>(OtherActor))
	{
		if (ShooterCharacter->NetworkCurrencyComponent->CurrentCurrency >= PickupItemData->Price)
		{
			if (PickupItemData && PickupItemData->ItemManagerClass)
			{
				if (APlayerState* PlayerState = ShooterCharacter->GetPlayerState())
				{
					if (UItemManagerComponentBase* ItemManager = Cast<UItemManagerComponentBase>(PlayerState->GetComponentByClass(PickupItemData->ItemManagerClass)))
					{
						ItemManager->AddItem_SER( FItemBaseData::CreateItem(PickupItemData->InventoryItemBaseData));
						ShooterCharacter->NetworkCurrencyComponent->CurrentCurrency -= PickupItemData->Price; // decress the players currency
					}
				}
			}
			Destroy();
		}
		else
		{
			float t = ShooterCharacter->NetworkCurrencyComponent->CurrentCurrency;;
		}
	}
}

// Called every frame
void AItemPickupBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

