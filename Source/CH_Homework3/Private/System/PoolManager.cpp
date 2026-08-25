#include "System/PoolManager.h"
#include "DataTables/TableItemSpawn.h"
#include "System/PoolBase.h"

APoolManager::APoolManager()
{
	ItemSpawnTable = nullptr;
}

APoolBase* APoolManager::AddPool(TSubclassOf<APoolingObject> PoolingClass, int32 PoolSize)
{
	if (PoolsMap.Contains(PoolingClass)) {
		return PoolsMap[PoolingClass];
	}

	APoolBase* NewPool = GetWorld()->SpawnActor<APoolBase>();
	NewPool->InitalizePool(PoolingClass, PoolSize);
	PoolsMap.Add(PoolingClass, NewPool);
	return NewPool;
}

APoolingObject* APoolManager::GetRandomItem()
{
	if (!ItemSpawnTable) {
		UE_LOG(LogTemp, Warning, TEXT("APoolManager::GetRandomItem, ItemSpawnTable is Null"));
		return nullptr;
	} 

	TArray<FTableItemSpawn*> AllRows;
	static const FString ContextString(TEXT("APoolManager::GetRandomItem"));
	ItemSpawnTable->GetAllRows(ContextString, AllRows);

	if (AllRows.IsEmpty()) {
		UE_LOG(LogTemp, Warning, TEXT("APoolManager::GetRandomItem, AllRows is Empty"));
		return nullptr;
	}

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
		UE_LOG(LogTemp, Warning, TEXT("APoolManager::GetRandomItem, SpawnClass is Null"));
		return nullptr;
	}

	APoolBase* SelectedPool = PoolsMap[SpawnClass];
	if (!SelectedPool) {
		UE_LOG(LogTemp, Warning, TEXT("APoolManager::GetRandomItem, SelectedPool is Null"));
		return nullptr;
	}

	return SelectedPool->Acquire();
}

void APoolManager::SetItemSpawnTable(UDataTable* NewItemSpawnTable)
{
	ItemSpawnTable = NewItemSpawnTable;
}

