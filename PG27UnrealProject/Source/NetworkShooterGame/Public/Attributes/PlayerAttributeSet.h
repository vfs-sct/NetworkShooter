// VFS Rohit 2025-2026

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "PlayerAttributeSet.generated.h"

/**
 * 
 */

UCLASS()
class NETWORKSHOOTERGAME_API UPlayerAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

	protected:
	// Energy Attribute
	UPROPERTY(BlueprintReadWrite, ReplicatedUsing = "OnRep_Energy", Category = "Attributes")
	FGameplayAttributeData Energy;

public:

	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UPlayerAttributeSet, Energy);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(Energy);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(Energy);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Energy);


	UFUNCTION()
	virtual void OnRep_Energy(const FGameplayAttributeData& OldEnergy);

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	
};
