// VFS Rohit 2025-2026


#include "Components/NetworkCurrencyComponent.h"

// Sets default values for this component's properties
UNetworkCurrencyComponent::UNetworkCurrencyComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicatedByDefault(true);
	bWantsInitializeComponent = true;
	// ...
}


float UNetworkCurrencyComponent::GetCurrentCurrency()
{
	return CurrentCurrency;
}

// Called when the game starts
void UNetworkCurrencyComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UNetworkCurrencyComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

