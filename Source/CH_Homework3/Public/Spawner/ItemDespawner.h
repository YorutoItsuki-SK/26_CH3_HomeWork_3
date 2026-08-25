#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemDespawner.generated.h"

class UBoxComponent;
class AItemBase;

UCLASS()
class CH_HOMEWORK3_API AItemDespawner : public AActor
{
	GENERATED_BODY()
	
public:	
	AItemDespawner();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
	USceneComponent* Scene;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
	UBoxComponent* DeSpawningBox;

	UFUNCTION()
	void DeSpawnItem(AItemBase* TriggeredItem);

	UFUNCTION()
	virtual void OnOverlapStart(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);
};
