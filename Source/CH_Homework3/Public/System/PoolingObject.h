#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PoolingObject.generated.h"

class APoolBase;

UENUM()
enum class EPoolingObjectState : uint8
{
	InPool,
	Active
};

UCLASS()
class CH_HOMEWORK3_API APoolingObject : public AActor
{
	GENERATED_BODY()
	
public:	
	APoolingObject();

	UFUNCTION(BlueprintCallable, Category = "Pool")
	virtual void OnAcquire(bool bNeedTick = false);
	UFUNCTION(BlueprintCallable, Category = "Pool")
	virtual void OnRelease();

	UFUNCTION(BlueprintCallable, Category = "Pool")
	void SetPool(APoolBase* NewPool);
	UFUNCTION(BlueprintCallable, Category = "Pool")
	virtual void ReturnToPool();

	EPoolingObjectState GetPoolState() const;

protected:
	UPROPERTY()
	TObjectPtr<APoolBase> Pool;

	EPoolingObjectState PoolState;

	void SetPoolState(EPoolingObjectState NewState);

	friend class APoolBase;

};
