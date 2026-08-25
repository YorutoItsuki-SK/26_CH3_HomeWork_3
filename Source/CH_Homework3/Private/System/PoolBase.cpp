#include "System/PoolBase.h"
#include "System/PoolingObject.h"

APoolBase::APoolBase()
{
	AllObjects = {};
	AvailableObjects = {};
	ObjectClassSaved = nullptr;
}

void APoolBase::InitalizePool(TSubclassOf<APoolingObject> ObjectClass, int32 PoolSize)
{
	if (ObjectClassSaved) {
		return;
	}
	ObjectClassSaved = ObjectClass;
	for (int32 i = 0; i < PoolSize; i++) {
		APoolingObject* NewObject =
			GetWorld()->SpawnActor<APoolingObject>(ObjectClass);

		if (NewObject) {
			NewObject->SetPool(this);
			AllObjects.Add(NewObject);
			AvailableObjects.Add(NewObject);
		}
	}
}

APoolingObject* APoolBase::Acquire()
{
	if (AvailableObjects.IsEmpty()) {
		APoolingObject* NewObject =
			GetWorld()->SpawnActor<APoolingObject>(ObjectClassSaved);
		NewObject->SetPool(this);
		AllObjects.Add(NewObject);
		NewObject->SetPoolState(EPoolingObjectState::Active);
		return NewObject;
	}
	APoolingObject* PopedObject = AvailableObjects.Pop();
	PopedObject->SetPoolState(EPoolingObjectState::Active);
	return PopedObject;
}

void APoolBase::Release(APoolingObject* Object)
{
	if (!Object) {
		return;
	}
	if (Object->GetPoolState() == EPoolingObjectState::InPool) {
		return;
	}
	Object->SetPoolState(EPoolingObjectState::InPool);
	Object->OnRelease();
	AvailableObjects.Push(Object);
}

