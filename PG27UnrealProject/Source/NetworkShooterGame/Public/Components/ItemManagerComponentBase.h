// VFS Rohit 2025-2026

#pragma once

#include "CoreMinimal.h"
#include "Actors/ItemBase.h"
#include "Components/ActorComponent.h"
#include "ItemManagerComponentBase.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), BlueprintType, Blueprintable )
class NETWORKSHOOTERGAME_API UItemManagerComponentBase : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UItemManagerComponentBase();

	UFUNCTION(Server, Reliable)
	void AddItem_SER(FItemBaseData ItemTypeToAdd);

	UFUNCTION(Server, Reliable)
	void RemoveItem_SER(FItemBaseData ItemTypeToRemove, const int32 ItemCountToRemove);

	UFUNCTION(BlueprintCallable)
	AItemBase* GetCurrentItem();

	// _Implemnetioatn :  Networked Function / BlueprintNativeEvent
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent)
	void OnItemAdded(FItemBaseData NewItemTypeAdded);


	UPROPERTY(BlueprintReadOnly, Replicated)
	TArray<FItemBaseData> Items;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Items")
	TArray<TSubclassOf<AItemBase>> ItemClassesToAllow;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Items")
	int32 MaxItemCount = 1;

	UPROPERTY(BlueprintReadWrite, Replicated,  Category="Items")
	TObjectPtr<AItemBase> CurrentItem;

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
