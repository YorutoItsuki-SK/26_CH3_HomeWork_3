#pragma once

#include "CoreMinimal.h"
#include "System/PoolingObject.h"
#include "ItemBase.generated.h"

class USphereComponent;
class UWidgetComponent;
class AItemSpawnVolume;

UCLASS()
class CH_HOMEWORK3_API AItemBase : public APoolingObject
{
	GENERATED_BODY()

public:
	AItemBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Name")
	FString ItemName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Desc")
	FString ItemDesc;

	UFUNCTION()
	virtual void ActivateItem(AActor* Activator);

	UFUNCTION()
	virtual void Deploy(FVector Location);

	void MoveX(float DeltaSpeed);

	void SetSpawner(AItemSpawnVolume* NewItemSpawnVolume);

	virtual void ReturnToPool() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Component")
	USceneComponent* Scene;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Component")
	UStaticMeshComponent* StaticMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Component")
	USphereComponent* CollisionActive;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Component")
	USphereComponent* CollisionUi;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Effect")
	USoundBase* PickupSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Effect")
	UParticleSystem* Particle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Effect")
	UWidgetComponent* ItemWidget;

	bool bIsActivated = true;

	virtual void BeginPlay() override;

	FTimerHandle SpawnTimer;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Spawner")
	TWeakObjectPtr<AItemSpawnVolume> Spawner;

	UFUNCTION()
	virtual void OnOverlapStartWidget(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);
	UFUNCTION()
	virtual void OnOverlapEndWidget(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex
	);
	UFUNCTION()
	virtual void OnOverlapStartActive(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);
	UFUNCTION()
	virtual void OnOverlapEndActive(
		UPrimitiveComponent* OverLappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex
	);
};
