// VFS Rohit 2025-2026


#include "NetworkShooterPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

void ANetworkShooterPlayerController::LookPitchChange(const FInputActionValue& PitchValue)
{
	AddPitchInput(PitchValue.Get<float>());
}

void ANetworkShooterPlayerController::LookYawChange(const FInputActionValue& YawValue)
{
	AddYawInput(YawValue.Get<float>());
}

void ANetworkShooterPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (IsLocalController())
	{
		if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
		{
			if (UEnhancedInputLocalPlayerSubsystem* EnhancedInputLocalPlayerSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer))
			{
				if (DefaultInputMappingContext)
				{
					FModifyContextOptions Options;
					Options.bForceImmediately = false;
					Options.bNotifyUserSettings = true;
					Options.bIgnoreAllPressedKeysUntilRelease = true;
					EnhancedInputLocalPlayerSubsystem->AddMappingContext(DefaultInputMappingContext, 0, Options);
				}
			}

			if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
			{
				if (LookPitchInputAction)
				{
					EnhancedInputComponent->BindAction(LookPitchInputAction, ETriggerEvent::Triggered, this, &ANetworkShooterPlayerController::LookPitchChange);
				}

				if (LookYawInputAction)
				{
					EnhancedInputComponent->BindAction(LookYawInputAction, ETriggerEvent::Triggered, this, &ANetworkShooterPlayerController::LookYawChange);
				}
			}
		}
	}
}
