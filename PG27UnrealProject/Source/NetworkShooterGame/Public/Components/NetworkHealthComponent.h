// VFS Rohit 2025-2026

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NetworkHealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, float, OldHealth, float, NewHealth);

class UDamageType;
class AController;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NETWORKSHOOTERGAME_API UNetworkHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UNetworkHealthComponent();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health", meta = (ClampMin = 0, ClampMax = 1000))
	float MaxHealth = 100.0f;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = "OnRep_Health", Transient, Category = "Health")
	float CurrentHealth;

	UPROPERTY(BlueprintReadOnly, Replicated, Category = "Health", Transient)
	float OldHealth;

	UFUNCTION(Server, Reliable)
	void TakeDamage_SER(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser );

	UFUNCTION(Category = "Health")
	virtual void OnRep_Health();

	// this function allows us to register variables to be networked
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(BlueprintAssignable, BlueprintReadOnly, Category = "Health")
	FOnHealthChanged OnHealthChangedDelegate;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void InitializeComponent() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
