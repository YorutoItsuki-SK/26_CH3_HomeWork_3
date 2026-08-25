#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemSpawnVolume.generated.h"

class UBoxComponent;
class APoolManager;
class AItemBase;

UCLASS()
class CH_HOMEWORK3_API AItemSpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	AItemSpawnVolume();

	void SpawnRandomItem();

	void ReportDespawn(AItemBase* DespawnedItem);

	virtual void Tick(float DeltaTime) override;

	void BeltStop();

	void BeltStart(float NewSpeed);

protected:

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
	USceneComponent* Scene;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
	UBoxComponent* SpawningBox;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
	APoolManager* PoolManager;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	UDataTable* TableItems;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
	TSet<AItemBase*> PendingDespawnItems;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
	TSet<AItemBase*> SpawnedItems;

	float SpeedMoveX;

};
