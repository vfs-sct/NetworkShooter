// VFS Rohit 2025-2026


#include "NetworkShooterPlayerState.h"
#include "Net/UnrealNetwork.h"
#include "GameplayAbilities/Public/AbilitySystemComponent.h"
#include "Components/ItemManagerComponentBase.h"

ANetworkShooterPlayerState::ANetworkShooterPlayerState()
{
	PrimaryWeaponManager = CreateDefaultSubobject<UItemManagerComponentBase>(TEXT("PrimaryWeaponManager"));
	InventoryManager = CreateDefaultSubobject<UItemManagerComponentBase>(TEXT("InventoryManager"));
	NetworkAbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("NetworkAbilitySystemComponent"));
	NetworkAbilitySystemComponent->SetOwnerActor(this);
	NetworkAbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Full);
}

UAbilitySystemComponent* ANetworkShooterPlayerState::GetAbilitySystemComponent() const
{
	return NetworkAbilitySystemComponent;
}

void ANetworkShooterPlayerState::OnNetworkPawnSet(APlayerState* Player, APawn* NewPawn, APawn* OldPawn)
{
	if (NetworkAbilitySystemComponent)
	{
		NetworkAbilitySystemComponent->SetAvatarActor(NewPawn);
	}
}

void ANetworkShooterPlayerState::BeginPlay()
{
	Super::BeginPlay();

	OnPawnSet.AddUniqueDynamic(this, &ANetworkShooterPlayerState::OnNetworkPawnSet);
}

void ANetworkShooterPlayerState::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ANetworkShooterPlayerState, InventoryManager);
	DOREPLIFETIME(ANetworkShooterPlayerState, PrimaryWeaponManager);
}
