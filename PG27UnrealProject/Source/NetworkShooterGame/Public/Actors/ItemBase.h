// VFS Rohit 2025-2026

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnItemUsed);

class AItemBase;

USTRUCT(BlueprintType)
struct FItemBaseData
{
	GENERATED_BODY()

	FItemBaseData()
	{
		UniqueId = FGuid::NewGuid();
		ClassToSpawn = nullptr;
		MaxCountAllowed = 1;
	}

	FItemBaseData(const FItemBaseData& ItemToCopy)
	{
		UniqueId = ItemToCopy.UniqueId;
		ClassToSpawn = ItemToCopy.ClassToSpawn;
		MaxCountAllowed = ItemToCopy.MaxCountAllowed;
	}

	FItemBaseData& operator=(const FItemBaseData& ItemToCopy)
	{
		if (this != &ItemToCopy)
		{
			ClassToSpawn = ItemToCopy.ClassToSpawn;
			MaxCountAllowed = ItemToCopy.MaxCountAllowed;
			UniqueId =ItemToCopy.UniqueId;
		}
		return *this;
	}

	static FItemBaseData inline CreateItem(const FItemBaseData& ItemToCopy)
	{
		FItemBaseData NewItem = ItemToCopy;
		NewItem.UniqueId = FGuid::NewGuid();
		return NewItem;
	}
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AItemBase> ClassToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxCountAllowed;

	UPROPERTY(BlueprintReadOnly)
	FGuid UniqueId;

	bool operator==(const FItemBaseData& other) const
	{
		return UniqueId == other.UniqueId;
	}
};


UCLASS()
class NETWORKSHOOTERGAME_API AItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemBase();

	// Override this per Item Type
	UFUNCTION(BlueprintCallable, Server, Reliable)
	virtual void UseItem_SER();

	UFUNCTION(BlueprintNativeEvent, meta = (DisplayName = "On Use Item"))
	void BP_OnUseItem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintAssignable)
	FOnItemUsed OnItemUsed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
