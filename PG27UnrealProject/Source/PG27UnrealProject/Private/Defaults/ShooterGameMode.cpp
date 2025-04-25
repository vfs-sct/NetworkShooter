// VFS Rohit 2025-2026


#include "Defaults/ShooterGameMode.h"
#include "Engine.h"

void AShooterGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, TimeToShowPrint, PrintColor, PrintMessage);
	}
}
