#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PoolManager.generated.h"

class APoolBase;
class APoolingObject;

UCLASS()
class CH_HOMEWORK3_API APoolManager : public AActor
{
	GENERATED_BODY()
	
public:	
	APoolManager();

	APoolBase* AddPool(TSubclassOf<APoolingObject> PoolingClass, int32 PoolSize);

	UFUNCTION(BlueprintCallable, Category = "Pool")
	APoolingObject* GetRandomItem();
	UFUNCTION(BlueprintCallable, Category = "Pool")
	void SetItemSpawnTable(UDataTable* NewItemSpawnTable);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pool")
	TMap<TSubclassOf<APoolingObject>, APoolBase*> PoolsMap;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pool")
	UDataTable* ItemSpawnTable;
};
