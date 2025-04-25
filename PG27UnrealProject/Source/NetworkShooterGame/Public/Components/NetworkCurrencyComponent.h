// VFS Rohit 2025-2026

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NetworkCurrencyComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NETWORKSHOOTERGAME_API UNetworkCurrencyComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UNetworkCurrencyComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentCurrency;

	UFUNCTION(BlueprintCallable, Category = "Currency")
	float GetCurrentCurrency();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
