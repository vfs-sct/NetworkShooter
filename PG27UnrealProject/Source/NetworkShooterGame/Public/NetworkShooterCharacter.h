// VFS Rohit 2025-2026

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputAction.h"
#include "AbilitySystemInterface.h"
#include "NetworkShooterCharacter.generated.h"

class UPlayerAttributeSet;
class UInputMappingContext;
class UNetworkHealthComponent;
class UNetworkCurrencyComponent;
class UItemManagerComponentBase;



UCLASS()
class NETWORKSHOOTERGAME_API ANetworkShooterCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANetworkShooterCharacter();

	// Inputs
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputAction> HorizontalMovementInputAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputAction> VerticalMovementInputAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputAction> JumpInputAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputAction> PrimaryFireInputAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputMappingContext> CombatMappingContext;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Components")
	TObjectPtr<UNetworkHealthComponent> NetworkHealthComponent;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Components")
	TObjectPtr<UNetworkCurrencyComponent> NetworkCurrencyComponent;
	
	// Overrides from IAbilitySystemInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input")
	const UPlayerAttributeSet* PlayerAttributes;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void MovementInput(const FInputActionInstance& Instance);

	UFUNCTION()
	void PrimaryFire(const FInputActionValue& Value);

};
