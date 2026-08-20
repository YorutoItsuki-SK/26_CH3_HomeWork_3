#include "System/PoolManager.h"
#include "DataTables/TableItemSpawn.h"
#include "System/PoolBase.h"

APoolManager::APoolManager()
{

}

APoolBase* APoolManager::AddPool(TSubclassOf<APoolingObject> PoolingClass, APoolBase* NewPool)
{
	if (PoolsMap.Contains(PoolingClass)) {
		return PoolsMap[PoolingClass];
	}
	PoolsMap.Add(PoolingClass, NewPool);
	return NewPool;
}

APoolingObject* APoolManager::GetRandomItem()
{
	if (!ItemSpawnTable) return nullptr;

	TArray<FTableItemSpawn*> AllRows;
	static const FString ContextString(TEXT("APoolManager::GetRandomItem"));
	ItemSpawnTable->GetAllRows(ContextString, AllRows);

	if (AllRows.IsEmpty()) return nullptr;

	float TotalChance = 0.f;
	for (const FTableItemSpawn* Row : AllRows) {
		if (!Row) {
			continue;
		}
		TotalChance += Row->SpawnChance;
	}

	const float RandValue = FMath::FRandRange(0.f, TotalChance);
	float StackedChance = 0.f;

	TSubclassOf<AItemBase> SpawnClass = nullptr;

	for (FTableItemSpawn* Row : AllRows) {
		if (!Row) {
			continue;
		}
		StackedChance += Row->SpawnChance;
		if (RandValue <= StackedChance) {
			SpawnClass = Row->ItemClass;
			break;
		}
	}

	if (!SpawnClass) {
		return nullptr;
	}

	APoolBase* SelectedPool = PoolsMap[SpawnClass];
	if (!SelectedPool) {
		return nullptr;
	}

	return SelectedPool->Acquire();
}

void APoolManager::SetItemSpawnTable(UDataTable* NewItemSpawnTable)
{
	ItemSpawnTable = NewItemSpawnTable;
}

