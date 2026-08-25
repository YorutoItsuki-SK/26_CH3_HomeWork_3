#include "System/PoolingObject.h"
#include "System/PoolBase.h"

APoolingObject::APoolingObject()
{
	PrimaryActorTick.bCanEverTick = false;

	Pool = nullptr;
	PoolState = EPoolingObjectState::InPool; 
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
}

void APoolingObject::OnAcquire(bool bNeedTick)
{
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	SetActorTickEnabled(bNeedTick);
}

void APoolingObject::OnRelease()
{
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	SetActorTickEnabled(false);
}

void APoolingObject::SetPool(APoolBase* NewPool)
{
	if (!IsValid(NewPool)) {
		UE_LOG(LogTemp, Warning, TEXT("APoolingObject::SetPool, Pool is Null"));
		return;
	}
	Pool = NewPool;
}

void APoolingObject::ReturnToPool() {
	if (!Pool) {
		UE_LOG(LogTemp, Warning, TEXT("APoolingObject::ReturnToPool, Pool is Null"));
		return;
	}
	Pool->Release(this);
}

EPoolingObjectState APoolingObject::GetPoolState() const
{
	return PoolState;
}

void APoolingObject::SetPoolState(EPoolingObjectState NewState)
{
	PoolState = NewState;
}

