#include "BeltGameState.h"
#include "Items/ItemBase.h"
#include "System/PoolManager.h"
#include "DataTables/TableItemSpawn.h"
#include "DataTables/TableWave.h"
#include "Spawner/ItemSpawnVolume.h"
#include "BeltGameInstance.h"
#include "Controller/TestPlayerController.h"

ABeltGameState::ABeltGameState() {
	PrimaryActorTick.bCanEverTick = false;

	Score = 0;
}

void ABeltGameState::BeginPlay() {
	Super::BeginPlay();
}

int32 ABeltGameState::GetScore() const {
	return Score;
}

void ABeltGameState::AddScore(int32 Amount) {
	Score += Amount;
}

void ABeltGameState::UpdateHUD()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (!PlayerController) {
		return;
	}
	ATestPlayerController* TestPlayerController = Cast<ATestPlayerController>(PlayerController);
	if (!TestPlayerController) {
		return;
	}
	UUserWidget* HUDWidget = TestPlayerController->GetHUDWidget();
	if (!HUDWidget) {
		return;
	}
}

void ABeltGameState::OnGameOver()
{
}

UDataTable* ABeltGameState::GetWaveData() const
{
	UGameInstance* GameInstanceRaw = GetGameInstance();
	if (!GameInstanceRaw) {
		UE_LOG(LogTemp, Warning, TEXT("ABeltGameState::GetWaveData is GameInstanceRaw is Null"));
		return nullptr;
	}
	UBeltGameInstance* GameInstance = Cast<UBeltGameInstance>(GameInstanceRaw);
	if (!GameInstance) {
		UE_LOG(LogTemp, Warning, TEXT("ABeltGameState::GetWaveData is GameInstance is Null"));
		return nullptr;
	}

	return GameInstance->GetTableWave();
}
