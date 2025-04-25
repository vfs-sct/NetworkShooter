// VFS Rohit 2025-2026


#include "Components/NetworkHealthComponent.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UNetworkHealthComponent::UNetworkHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
	bWantsInitializeComponent = true;
	// ...
}


void UNetworkHealthComponent::TakeDamage_SER_Implementation(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (DamagedActor == GetOwner())
	{
		OldHealth = CurrentHealth;
		CurrentHealth = FMath::Clamp<float>(CurrentHealth - Damage, 0.0f, MaxHealth);
		OnRep_Health();
	}
}

void UNetworkHealthComponent::OnRep_Health()
{
	OnHealthChangedDelegate.Broadcast(OldHealth, CurrentHealth);
}

void UNetworkHealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Register Networked Properties
	DOREPLIFETIME(UNetworkHealthComponent, CurrentHealth);
	DOREPLIFETIME(UNetworkHealthComponent, OldHealth);
}

// Called when the game starts
void UNetworkHealthComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UNetworkHealthComponent::InitializeComponent()
{
	Super::InitializeComponent();

	if (AActor* Owner = GetOwner())
	{
		if (Owner->HasAuthority())
		{
			Owner->OnTakeAnyDamage.AddUniqueDynamic(this, &UNetworkHealthComponent::TakeDamage_SER);
			OldHealth = MaxHealth;
			CurrentHealth = MaxHealth;
			OnRep_Health();
		}
	}
}


// Called every frame
void UNetworkHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

