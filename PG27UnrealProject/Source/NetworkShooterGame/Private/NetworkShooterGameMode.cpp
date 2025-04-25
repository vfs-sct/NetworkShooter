// VFS Rohit 2025-2026


#include "NetworkShooterGameMode.h"
#include "NetworkShooterGameState.h"
#include "NetworkShooterGameSession.h"
#include "NetworkShooterPlayerController.h"
#include "NetworkShooterHUD.h"
#include "NetworkShooterCharacter.h"
#include "TimerManager.h"
#include "Data/GameModeSettings.h"
#include "Engine.h"
#include "NetworkShooterPlayerState.h"
#include "NetworkShooterSpawnPoints.h"
#include "EngineUtils.h"


ANetworkShooterGameMode::ANetworkShooterGameMode()
{
	GameStateClass = ANetworkShooterGameState::StaticClass();
	GameSessionClass = ANetworkShooterGameSession::StaticClass();
	PlayerControllerClass = ANetworkShooterPlayerController::StaticClass();
	DefaultPawnClass = ANetworkShooterCharacter::StaticClass();
	HUDClass = ANetworkShooterHUD::StaticClass();
	PlayerStateClass = ANetworkShooterPlayerState::StaticClass();

	bStartPlayersAsSpectators = true;
}

bool ANetworkShooterGameMode::ReadyToStartMatch_Implementation()
{
	return GetNumPlayers() >= GameSession->MaxPlayers;
}

void ANetworkShooterGameMode::HandleMatchHasStarted()
{
	Super::HandleMatchHasStarted();
	ActualGameTime = 0;
	GetWorldTimerManager().SetTimer(ActiveGameTimerHandle, this, &ThisClass::OnGameTimeUpdated, 1.0f, true);
}

bool ANetworkShooterGameMode::ReadyToEndMatch_Implementation()
{
	if (GameModeSettings)
	{
		return ActualGameTime >= GameModeSettings->GameTime;
	}
	return false;
}

void ANetworkShooterGameMode::HandleMatchHasEnded()
{
	GetWorldTimerManager().ClearTimer(ActiveGameTimerHandle);
	Super::HandleMatchHasEnded();
}

void ANetworkShooterGameMode::Tick(float InDeltaTime)
{
	Super::Tick(InDeltaTime);
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, .01f, FColor::Magenta, GetMatchState().ToString());
	}
}

AActor* ANetworkShooterGameMode::ChoosePlayerStart_Implementation(AController* Player)
{
	TArray<ANetworkShooterSpawnPoints*> FoundSpawnPoints;
	if (SpawnPointClass)
	{
		for (TActorIterator<ANetworkShooterSpawnPoints> It(GetWorld()); It; ++It)
		{
			if (It->IsA(SpawnPointClass))
			{
				FoundSpawnPoints.AddUnique(*It);
			}
		}
	}

	if (ANetworkShooterGameState* CurrentGameState = GetGameState<ANetworkShooterGameState>())
	{
		for (const APlayerState* PlayerState : CurrentGameState->PlayerArray)
		{
			if (PlayerState->GetPlayerId() == Player->PlayerState->GetPlayerId())
			{
				const int32 Index = CurrentGameState->PlayerArray.IndexOfByKey(PlayerState);
				
				if (FoundSpawnPoints.IsValidIndex(Index))
				{
					return FoundSpawnPoints[Index];
				}
			}
		}
	}

	return this;
}

void ANetworkShooterGameMode::InitStartSpot_Implementation(AActor* StartSpot, AController* NewPlayer)
{
	if (DefaultPawnClass && StartSpot && NewPlayer)
	{
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Owner = NewPlayer;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		if (UWorld* World = GetWorld())
		{
			if (APawn* OwningPawn = NewPlayer->GetPawn())
			{
				NewPlayer->UnPossess();
				OwningPawn->Destroy();
			}
			
			if (APawn* NewPawn = World->SpawnActor<APawn>(DefaultPawnClass, StartSpot->GetActorLocation(), StartSpot->GetActorRotation(), SpawnParameters))
			{
				NewPlayer->Possess(NewPawn);
			}
		}
	}
}

void ANetworkShooterGameMode::OnGameTimeUpdated()
{
	++ActualGameTime;
}
