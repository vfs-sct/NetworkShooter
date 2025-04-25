// VFS Rohit 2025-2026


#include "NetworkShooterCharacter.h"

#include "AbilitySystemComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "NetworkShooterPlayerState.h"
#include "Components/ItemManagerComponentBase.h"
#include "Attributes/PlayerAttributeSet.h"
#include "Components/NetworkCurrencyComponent.h"
#include "Components/NetworkHealthComponent.h"

// Sets default values
ANetworkShooterCharacter::ANetworkShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	NetworkHealthComponent = CreateDefaultSubobject<UNetworkHealthComponent>(TEXT("NetworkHealthComponent"));
	NetworkCurrencyComponent = CreateDefaultSubobject<UNetworkCurrencyComponent>(TEXT("NetworkCurrencyComponent"));
}

UAbilitySystemComponent* ANetworkShooterCharacter::GetAbilitySystemComponent() const
{
	if (ANetworkShooterPlayerState* OwningPlayerState = GetPlayerState<ANetworkShooterPlayerState>())
	{
		return OwningPlayerState->GetAbilitySystemComponent();
	}
	return nullptr;
}

// Called when the game starts or when spawned
void ANetworkShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (UAbilitySystemComponent* AbilitySystemComponent = GetAbilitySystemComponent())
	{
		PlayerAttributes = AbilitySystemComponent->GetSet<UPlayerAttributeSet>();
	}
}

// Called every frame
void ANetworkShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANetworkShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (IsLocallyControlled())
	{
		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
		{
			if (CombatMappingContext)
			{
				if (APlayerController* PlayerController = GetController<APlayerController>())
				{
					if (ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer())
					{
						if (UEnhancedInputLocalPlayerSubsystem* EnhancedInputLocalPlayerSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer))
						{
							EnhancedInputLocalPlayerSubsystem->AddMappingContext(CombatMappingContext,1);
						}
					}
				}
			}
			if (HorizontalMovementInputAction)
			{
				EnhancedInputComponent->BindAction(HorizontalMovementInputAction, ETriggerEvent::Triggered, this, &ANetworkShooterCharacter::MovementInput);
			}

			if (VerticalMovementInputAction)
			{
				EnhancedInputComponent->BindAction(VerticalMovementInputAction, ETriggerEvent::Triggered, this, &ANetworkShooterCharacter::MovementInput);
			}

			if (JumpInputAction)
			{
				EnhancedInputComponent->BindAction(JumpInputAction, ETriggerEvent::Triggered, this, &ANetworkShooterCharacter::Jump);
			}

			if (PrimaryFireInputAction)
			{
				EnhancedInputComponent->BindAction(PrimaryFireInputAction, ETriggerEvent::Triggered, this, &ANetworkShooterCharacter::PrimaryFire);
			}
		}
	}

}

void ANetworkShooterCharacter::MovementInput(const FInputActionInstance& Instance)
{
	//@TODO : Do your cool movement stuff here;
	if (Instance.GetSourceAction() == HorizontalMovementInputAction)
	{
		AddMovementInput(GetActorRightVector(), Instance.GetValue().Get<float>(), false );
	}

	if (Instance.GetSourceAction() == VerticalMovementInputAction)
	{
		AddMovementInput(GetActorForwardVector(), Instance.GetValue().Get<float>(), false );
	}
}

void ANetworkShooterCharacter::PrimaryFire(const FInputActionValue& Value)
{
	if (ANetworkShooterPlayerState* LocalPlayerState = GetPlayerState<ANetworkShooterPlayerState>())
	{
		if (UItemManagerComponentBase* PrimaryWeaponManager =  LocalPlayerState->PrimaryWeaponManager)
		{
			if (AItemBase* PrimaryWeapon = PrimaryWeaponManager->GetCurrentItem())
			{
				PrimaryWeapon->UseItem_SER();
			}
		}
	}
}
