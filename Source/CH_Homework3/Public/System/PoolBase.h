#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PoolBase.generated.h"

class APoolingObject;

UCLASS()
class CH_HOMEWORK3_API APoolBase : public AActor
{
	GENERATED_BODY()
	
public:	
	APoolBase();

	void InitalizePool(
		TSubclassOf<APoolingObject> ObjectClass,
		int32 PoolSize
	);

	APoolingObject* Acquire();
	void Release(APoolingObject* Object);

private:
	UPROPERTY()
	TArray<TObjectPtr<APoolingObject>> AllObjects;
	UPROPERTY()
	TArray<TObjectPtr<APoolingObject>> AvailableObjects;

	UPROPERTY()
	TSubclassOf<APoolingObject> ObjectClassSaved;
};
