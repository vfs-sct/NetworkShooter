// VFS Rohit 2025-2026

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "ShooterGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PG27UNREALPROJECT_API AShooterGameMode : public AGameMode
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, BlueprintSetter="SetPrintColor", Category = "Print")
	FColor PrintColor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Print")
	float TimeToShowPrint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Print")
	FString PrintMessage;

	virtual void BeginPlay()  override;

	UFUNCTION(BlueprintSetter)
	void SetPrintColor(const FColor InValue) { PrintColor = InValue; };
	
};
