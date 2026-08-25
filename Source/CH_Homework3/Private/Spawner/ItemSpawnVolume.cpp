#include "Spawner/ItemSpawnVolume.h"
#include "Components/BoxComponent.h"
#include "System/PoolManager.h"
#include "Items/ItemBase.h"
#include "DataTables/TableItemSpawn.h"

AItemSpawnVolume::AItemSpawnVolume()
{
	PrimaryActorTick.bCanEverTick = true;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(Scene);
	SpawningBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	SpawningBox->SetupAttachment(Scene);

	PoolManager = nullptr;
	SpeedMoveX = 0.f;
	TableItems = nullptr;
}

void AItemSpawnVolume::BeginPlay()
{
	Super::BeginPlay();
	if (!TableItems) {
		UE_LOG(LogTemp, Warning, TEXT("AItemSpawnVolume::Initailize is TableItems is Null"));
		return;
	}
	PoolManager = GetWorld()->SpawnActor<APoolManager>();
	PoolManager->SetItemSpawnTable(TableItems);

	TArray<FTableItemSpawn*> AllRows;
	const FString ContextString(TEXT("AItemSpawnVolume::Initailize"));
	TableItems->GetAllRows(ContextString, AllRows);
	if (AllRows.IsEmpty()) {
		UE_LOG(LogTemp, Warning, TEXT("AItemSpawnVolume::Initailize is AllRows is IsEmpty"));
		return;
	}

	for (const FTableItemSpawn* Row : AllRows) {
		if (!Row) continue;
		PoolManager->AddPool(Row->ItemClass, 10);
	}
}

void AItemSpawnVolume::SpawnRandomItem()
{
	if (!PoolManager) {
		UE_LOG(LogTemp, Warning, TEXT("AItemSpawnVolume::SpawnRandomItem, PoolManager is Null"));
		return;
	}
	APoolingObject* NewObejct = PoolManager->GetRandomItem();
	if (!NewObejct) {
		UE_LOG(LogTemp, Warning, TEXT("AItemSpawnVolume::SpawnRandomItem, NewObejct is Null"));
		return;
	}
	AItemBase* NewItem = Cast<AItemBase>(NewObejct);

	if (!NewItem) {
		UE_LOG(LogTemp, Warning, TEXT("AItemSpawnVolume::SpawnRandomItem, NewItem is Null"));
		return;
	}

	FVector BoxExtent = SpawningBox->GetScaledBoxExtent();
	FVector BoxOrigin = SpawningBox->GetComponentLocation();

	NewItem->Deploy(BoxOrigin +
		FVector(
			0.f,
			int32(FMath::FRandRange(-BoxExtent.Y, BoxExtent.Y)),
			0.f
		)
	);
	NewItem->SetSpawner(this);
	SpawnedItems.Add(NewItem);
}

void AItemSpawnVolume::ReportDespawn(AItemBase* DespawnedItem)
{
	PendingDespawnItems.Add(DespawnedItem);
}

void AItemSpawnVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for (AItemBase* Item : PendingDespawnItems) {
		SpawnedItems.Remove(Item);
	}
	PendingDespawnItems.Empty();

	for (AItemBase* Item : SpawnedItems) {
		Item->MoveX(SpeedMoveX * DeltaTime);
	}
}

void AItemSpawnVolume::BeltStop()
{
	SetActorTickEnabled(false);

	for (AItemBase* Item : SpawnedItems) {
		Item->ReturnToPool();
	}
	PendingDespawnItems.Empty();
	SpawnedItems.Empty();
}

void AItemSpawnVolume::BeltStart(float NewSpeed)
{
	UE_LOG(LogTemp, Warning, TEXT("AItemSpawnVolume::BeltStart, %f"), NewSpeed);
	SpeedMoveX = NewSpeed;
	SetActorTickEnabled(true);
}

