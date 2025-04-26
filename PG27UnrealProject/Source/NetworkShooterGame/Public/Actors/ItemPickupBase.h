// VFS Rohit 2025-2026

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "ItemPickupBase.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class UItemPickupData;

UCLASS()
class NETWORKSHOOTERGAME_API AItemPickupBase : public AActor
{
	GENERATED_BODY()
public:	
	// Sets default values for this actor's properties
	AItemPickupBase();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemPickup")
	TObjectPtr<USphereComponent> CollisionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemPickup")
	TObjectPtr<UStaticMeshComponent> ItemMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemPickup")
	TObjectPtr<UItemPickupData> PickupItemData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemPickup")
	float Price = 0;
protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(Server, Reliable)
	void OnItemCollisionBegin_SER(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
