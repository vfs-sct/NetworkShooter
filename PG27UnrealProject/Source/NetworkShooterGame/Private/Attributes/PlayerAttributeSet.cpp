// VFS Rohit 2025-2026


#include "Attributes/PlayerAttributeSet.h"
#include "Net/UnrealNetwork.h"

void UPlayerAttributeSet::OnRep_Energy(const FGameplayAttributeData& OldEnergy)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSet, Energy, OldEnergy);
}

void UPlayerAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSet, Energy, COND_None, REPNOTIFY_Always);
}
