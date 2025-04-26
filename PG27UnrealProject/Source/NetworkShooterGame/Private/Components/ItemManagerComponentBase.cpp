// VFS Rohit 2025-2026


#include "Components/ItemManagerComponentBase.h"
#include "Actors/ItemBase.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UItemManagerComponentBase::UItemManagerComponentBase()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicatedByDefault(true);
	bWantsInitializeComponent = true;
	// ...
}


AItemBase* UItemManagerComponentBase::GetCurrentItem()
{
	return CurrentItem;
}

AItemBase* UItemManagerComponentBase::GetRecentlyAddedItem()
{
	if (Items.Num() > 0)
	{
		const FItemBaseData& LastItemData = Items.Last();
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Owner = GetOwner();

		return GetWorld()->SpawnActor<AItemBase>(LastItemData.ClassToSpawn, SpawnParameters);
	}
	return nullptr;
}

// Called when the game starts
void UItemManagerComponentBase::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UItemManagerComponentBase::OnItemAdded_Implementation(FItemBaseData NewItemTypeAdded)
{
}

void UItemManagerComponentBase::AddItem_SER_Implementation(FItemBaseData ItemTypeToAdd)
{
	if (ItemClassesToAllow.Contains(ItemTypeToAdd.ClassToSpawn))
	{

		if (Items.Num() < MaxItemCount)
		{
			Items.Add(ItemTypeToAdd);
			if (Items.Num() == 1)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "Item Added");
				FActorSpawnParameters SpawnParameters;
				SpawnParameters.Owner = GetOwner();
				CurrentItem = GetWorld()->SpawnActor<AItemBase>(ItemTypeToAdd.ClassToSpawn, SpawnParameters);
			}
			OnItemAdded(ItemTypeToAdd);
		}
	}
}

void UItemManagerComponentBase::RemoveItem_SER_Implementation(const FItemBaseData ItemTypeToRemove, const int32 ItemCountToRemove)
{
	TArray<FItemBaseData*> ItemsToRemove;
	for (FItemBaseData& ItemToRemove : Items)
	{
		if (ItemToRemove.ClassToSpawn == ItemTypeToRemove.ClassToSpawn)
		{
			if (ItemsToRemove.Num() < ItemCountToRemove)
			{
				ItemsToRemove.Add(&ItemToRemove);
			}
		}
	}

	for (FItemBaseData* ItemToRemove : ItemsToRemove)
	{
		Items.Remove(*ItemToRemove);
	}
}

void UItemManagerComponentBase::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UItemManagerComponentBase, Items);
	DOREPLIFETIME(UItemManagerComponentBase, CurrentItem);
}

// Called every frame
void UItemManagerComponentBase::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

