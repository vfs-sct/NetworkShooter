// VFS Rohit 2025-2026

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "NetworkShooterPlayerState.generated.h"


/**
 * 
 */
class UItemManagerComponentBase;

UCLASS()
class NETWORKSHOOTERGAME_API ANetworkShooterPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

	public:

	ANetworkShooterPlayerState();

	UPROPERTY(BlueprintReadOnly, Replicated, EditDefaultsOnly, Category = "Components")
	TObjectPtr<UItemManagerComponentBase> PrimaryWeaponManager;

	UPROPERTY(BlueprintReadOnly, Replicated, EditDefaultsOnly, Category = "Components")
	TObjectPtr<UItemManagerComponentBase> InventoryManager;

	UPROPERTY(BlueprintReadOnly, Replicated, EditDefaultsOnly, Category = "Components")
	TObjectPtr<UAbilitySystemComponent> NetworkAbilitySystemComponent;

	// Override from IAbilitySystemInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION()
	void OnNetworkPawnSet(APlayerState* Player, APawn* NewPawn, APawn* OldPawn);
	virtual void BeginPlay() override;
	
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
};
