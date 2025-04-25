// VFS Rohit 2025-2026

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/LocalPlayerSubsystem.h"
#include "ObjectPoolingSubsystem.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FObjectPoolingData
{
	GENERATED_BODY()

	UPROPERTY(Transient, BlueprintReadOnly)
	TArray<AActor*> Actors;
};

UCLASS()
class NETWORKSHOOTERGAME_API UObjectPoolingSubsystem : public ULocalPlayerSubsystem
{
	GENERATED_BODY()

	public:

	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION(BlueprintCallable)
	void PreWarmPool(TSubclassOf<AActor> PoolableClass, int32 Count);

	UFUNCTION(BlueprintCallable, meta=(DeterminesOutputType="PoolableClass") )
	AActor* SpawnActorFromPool(TSubclassOf<AActor> PoolableClass, const FTransform& Transform);

	UFUNCTION(BlueprintCallable)
	void ReturnToPool(AActor* Actor);


	protected:

	UPROPERTY()
	TMap<TSubclassOf<AActor>, FObjectPoolingData> ActorPools;
	
};
