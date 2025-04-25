// VFS Rohit 2025-2026

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "NetworkShooterPlayerController.generated.h"

/**
 * 
 */

class UInputMappingContext;
class UInputAction;

UCLASS()
class NETWORKSHOOTERGAME_API ANetworkShooterPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Network Shooter Game")
	TObjectPtr<UInputMappingContext> DefaultInputMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> LookPitchInputAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> LookYawInputAction;

	UFUNCTION()
	void LookPitchChange(const FInputActionValue& PitchValue);

	UFUNCTION()
	void LookYawChange(const FInputActionValue& YawValue);

	// Overrides
	virtual void SetupInputComponent() override;
	
};
