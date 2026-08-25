#include "BeltGameMode.h"
#include "Character/TestPawn.h"
#include "Controller/TestPlayerController.h"
#include "BeltGameState.h"
#include "Spawner/ItemSpawnVolume.h"
#include "Kismet/GameplayStatics.h"
#include "DataTables/TableWave.h"

ABeltGameMode::ABeltGameMode()
{
	DefaultPawnClass = ATestPawn::StaticClass();
	PlayerControllerClass = ATestPlayerController::StaticClass();
	GameStateClass = ABeltGameState::StaticClass();
	ItemSpawner = nullptr;
	CurrentWaveIndex = 0;
	TableWave = nullptr;
	ItemSpawnLeft = 0;
}

void ABeltGameMode::BeginPlay()
{
	TArray<AActor*> FoundVolumes;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AItemSpawnVolume::StaticClass(), FoundVolumes);

	if (FoundVolumes.IsEmpty()) {
		UE_LOG(LogTemp, Warning, TEXT("ABeltGameMode::BeginPlay, ItemSpawner is IsEmpty"));
		return;
	}
	ItemSpawner = Cast<AItemSpawnVolume>(FoundVolumes[0]);

	if (!ItemSpawner) {
		UE_LOG(LogTemp, Warning, TEXT("ABeltGameMode::BeginPlay, ItemSpawner is Null"));
		return;
	}

	ABeltGameState* BeltGameState = GetWorld()->GetGameState<ABeltGameState>();
	if (!BeltGameState) {
		UE_LOG(LogTemp, Warning, TEXT("ABeltGameMode::BeginPlay, BeltGameState is Null"));
		return;
	}

	TableWave = BeltGameState->GetWaveData();

	WaveStart();
}

void ABeltGameMode::WaveStart()
{
	if (!TableWave) {
		UE_LOG(LogTemp, Warning, TEXT("ABeltGameMode::WaveStart, TableWave is Null"));
		return;
	}

	if (!ItemSpawner) {
		UE_LOG(LogTemp, Warning, TEXT("ABeltGameMode::WaveStart, ItemSpawner is Null"));
		return;
	}
	
	TArray<FTableWave*> AllRows;

	FString ContextString(TEXT("ABeltGameMode::WaveStart"));
	TableWave->GetAllRows(ContextString, AllRows);

	if (AllRows.IsEmpty()) {
		UE_LOG(LogTemp, Warning, TEXT("ABeltGameMode::WaveStart, AllRows is Empty"));
		return;
	}

	if (CurrentWaveIndex >= AllRows.Num()) {
		return;
	}

	FTableWave* Row = AllRows[CurrentWaveIndex];

	if (GetWorldTimerManager().IsTimerActive(ItemSpawnTimer)) {
		GetWorldTimerManager().ClearTimer(ItemSpawnTimer);
		ItemSpawnLeft = 0;
		ItemDespawnLeft = 0;
	}

	ItemSpawner->BeltStart(-Row->BeltSpeed);
	ItemSpawnLeft = Row->SpawnCount;
	ItemDespawnLeft = Row->SpawnCount;

	GetWorldTimerManager().SetTimer(
		ItemSpawnTimer,
		this,
		&ABeltGameMode::WaveSpawnItem,
		Row->SpawnFrequency,
		true
	);
}

void ABeltGameMode::WaveSpawnItem()
{
	UE_LOG(LogTemp, Warning, TEXT("ABeltGameMode::WaveSpawnItem"));
	if (ItemSpawnLeft <= 0) {
		GetWorldTimerManager().ClearTimer(ItemSpawnTimer);
		return;
	}
	ItemSpawnLeft--;
	ItemSpawner->SpawnRandomItem();
}

void ABeltGameMode::ItemDespawned() {
	ItemDespawnLeft--;
	if (ItemDespawnLeft > 0) {
		return;
	}

	CurrentWaveIndex++;
	
	GetWorldTimerManager().SetTimer(
		WaveRestTimer,
		this,
		&ABeltGameMode::WaveStart,
		10.f,
		false
	);
}

void ABeltGameMode::GoToNextLevel()
{

}