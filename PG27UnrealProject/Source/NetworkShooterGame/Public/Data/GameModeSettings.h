// VFS Rohit 2025-2026

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameModeSettings.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class NETWORKSHOOTERGAME_API UGameModeSettings : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GameSettings")
	float GameTime = 30.0f;
	
};
