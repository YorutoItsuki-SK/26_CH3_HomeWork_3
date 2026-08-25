#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "BeltGameMode.generated.h"

class AItemSpawnVolume;

UCLASS()
class CH_HOMEWORK3_API ABeltGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	ABeltGameMode();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level")
	AItemSpawnVolume* ItemSpawner;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level")
	UDataTable* TableWave;

	void ItemDespawned();

	void GoToNextLevel();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Level")
	int32 CurrentWaveIndex;

	int32 ItemSpawnLeft;
	int32 ItemDespawnLeft;

	UFUNCTION(BlueprintCallable, Category = "Level")
	virtual void WaveStart();

	FTimerHandle ItemSpawnTimer;
	FTimerHandle WaveRestTimer;

	void WaveSpawnItem();
};
