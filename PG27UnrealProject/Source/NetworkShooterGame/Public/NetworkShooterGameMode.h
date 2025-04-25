// VFS Rohit 2025-2026

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "NetworkShooterGameMode.generated.h"

/**
 * 
 */
class UGameModeSettings;
class ANetworkShooterSpawnPoints;

UCLASS()
class NETWORKSHOOTERGAME_API ANetworkShooterGameMode : public AGameMode
{
	GENERATED_BODY()

public:

	ANetworkShooterGameMode();

	virtual bool ReadyToStartMatch_Implementation() override;
	virtual void HandleMatchHasStarted() override;
	virtual bool ReadyToEndMatch_Implementation() override;
	virtual void HandleMatchHasEnded() override;

	virtual void Tick(float InDeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings")
	TObjectPtr<UGameModeSettings> GameModeSettings;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings")
	TSubclassOf<ANetworkShooterSpawnPoints> SpawnPointClass;

	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;

	virtual void InitStartSpot_Implementation(AActor* StartSpot, AController* NewPlayer) override;
	
private:

	UPROPERTY(Transient)
	float ActualGameTime = 0.0f;

	UFUNCTION()
	void OnGameTimeUpdated();

	FTimerHandle ActiveGameTimerHandle;
};
