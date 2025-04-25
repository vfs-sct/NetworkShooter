// VFS Rohit 2025-2026

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PoolableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPoolableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class NETWORKSHOOTERGAME_API IPoolableInterface
{
	GENERATED_BODY()

	public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnPoolActorActivated();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnPoolActorDeactivated();

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
};
