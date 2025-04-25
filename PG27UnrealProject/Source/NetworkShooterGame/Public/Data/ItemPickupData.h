// VFS Rohit 2025-2026

#pragma once

#include "CoreMinimal.h"
#include "Actors/ItemBase.h"
#include "Engine/DataAsset.h"
#include "ItemPickupData.generated.h"

/**
 * 
 */
class UItemManagerComponentBase;
class UStaticMeshComponent;

UCLASS(Blueprintable, BlueprintType)
class NETWORKSHOOTERGAME_API UItemPickupData : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMesh> PickupMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FItemBaseData InventoryItemBaseData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UItemManagerComponentBase> ItemManagerClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Price = 20;
	
};
