// VFS Rohit 2025-2026


#include "Defaults/ShooterGameInstance.h"
#include "Engine.h"
#include "Logging/StructuredLog.h"

void UShooterGameInstance::Init()
{
	Super::Init();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5.0f, FColor::Magenta, TEXT("Hello World!"));
	}
	UE_LOGFMT(LogTemp, Warning, "Hello from {Name} !, I have {Amount} Score ", ("Name", GetName()), ("Amount", 55));
}
