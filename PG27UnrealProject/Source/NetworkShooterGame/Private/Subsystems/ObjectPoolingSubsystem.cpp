// VFS Rohit 2025-2026


#include "Subsystems/ObjectPoolingSubsystem.h"
#include "Engine.h"
#include "Interfaces/PoolableInterface.h"

bool UObjectPoolingSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	return true;	
}

void UObjectPoolingSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UObjectPoolingSubsystem::PreWarmPool(TSubclassOf<AActor> PoolableClass, int32 Count)
{
	if (!IsValid(PoolableClass) || !PoolableClass->ImplementsInterface(UPoolableInterface::StaticClass()) || Count < 1)
	{
		return;
	}
	
	FObjectPoolingData& Pool = ActorPools.FindOrAdd(PoolableClass);
	for (int32 i = 0; i < Count; i++)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		if (AActor* NewActor = GetWorld()->SpawnActor<AActor>(PoolableClass, FTransform::Identity, SpawnParams))
		{
			ReturnToPool(NewActor);
		}
	}
}

AActor* UObjectPoolingSubsystem::SpawnActorFromPool(TSubclassOf<AActor> PoolableClass, const FTransform& Transform)
{
	if (!IsValid(PoolableClass) || !PoolableClass->ImplementsInterface(UPoolableInterface::StaticClass()))
	{
		return nullptr;
	}
	
	FObjectPoolingData& Pool = ActorPools.FindOrAdd(PoolableClass);

	while (Pool.Actors.Num() > 0)
	{
		if (AActor* PooledActor = Pool.Actors.Pop())
		{
			PooledActor->SetActorTransform(Transform);
			PooledActor->SetActorHiddenInGame(false);
			PooledActor->SetActorEnableCollision(true);
			PooledActor->SetActorTickEnabled(true);
			IPoolableInterface::Execute_OnPoolActorActivated(PooledActor);
			return PooledActor;
		}
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	AActor* NewActor = GetWorld()->SpawnActor<AActor>(PoolableClass, Transform, SpawnParams);
	if (NewActor)
	{
		IPoolableInterface::Execute_OnPoolActorActivated(NewActor);
	}
	return NewActor;
}

void UObjectPoolingSubsystem::ReturnToPool(AActor* Actor)
{
	if (!IsValid(Actor) || !Actor->Implements<UPoolableInterface>())
	{
		return;
	}

	IPoolableInterface::Execute_OnPoolActorDeactivated(Actor);
	Actor->SetActorTransform(FTransform::Identity);
	Actor->SetActorLocation(FVector::ZeroVector);
	Actor->SetActorHiddenInGame(true);
	Actor->SetActorEnableCollision(false);
	Actor->SetActorTickEnabled(false);
	Actor->SetLifeSpan(0.f);
}
