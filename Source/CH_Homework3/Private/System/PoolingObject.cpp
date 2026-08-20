#include "System/PoolingObject.h"
#include "System/PoolBase.h"

APoolingObject::APoolingObject()
{
	Pool = nullptr;
	PoolState = EPoolingObjectState::InPool;
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
	if (!Pool) {
		return;
	}
	Pool = NewPool;
}

void APoolingObject::ReturnToPool() {
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

