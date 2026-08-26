#include "BeltGameState.h"
#include "Items/ItemBase.h"
#include "System/PoolManager.h"
#include "DataTables/TableItemSpawn.h"
#include "DataTables/TableWave.h"
#include "Spawner/ItemSpawnVolume.h"
#include "BeltGameInstance.h"
#include "Controller/TestPlayerController.h"
#include "Kismet/GameplayStatics.h"

ABeltGameState::ABeltGameState() {
	PrimaryActorTick.bCanEverTick = false;

	Score = 0;
}

void ABeltGameState::BeginPlay() {
	Super::BeginPlay();
	UGameInstance* GameInstanceRaw = GetGameInstance();
	if (!GameInstanceRaw) {
		return;
	}
	UBeltGameInstance* GameInstance = Cast<UBeltGameInstance>(GameInstanceRaw);
	if (!GameInstance) {
		UE_LOG(LogTemp, Warning, TEXT("ABeltGameState::BeginPlay, GameInstance is Null"));
		return;
	}
	Score = GameInstance->GetScore();
}

int32 ABeltGameState::GetScore() const {
	return Score;
}

void ABeltGameState::AddScore(int32 Amount) {
	Score += Amount;
}

void ABeltGameState::UpdateHUD()
{
}

void ABeltGameState::OnGameOver(bool bIsDead)
{
	APlayerController* PlayerControllerRaw = GetWorld()->GetFirstPlayerController();
	if (!PlayerControllerRaw) {
		return;
	}
	ATestPlayerController* PlayerController = Cast<ATestPlayerController>(PlayerControllerRaw);
	if (!PlayerController) {
		return;
	}
	PlayerController->SetPause(true);
	PlayerController->ShowMainMenu(bIsDead);
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

void ABeltGameState::EndLevel()
{
	UGameInstance* GameInstanceRaw = GetGameInstance();
	if (!GameInstanceRaw) {
		UE_LOG(LogTemp, Warning, TEXT("ABeltGameState::EndLevel, GameInstanceRaw is Null"));
		return;
	}
	UBeltGameInstance* GameInstance = Cast<UBeltGameInstance>(GameInstanceRaw);
	if (!GameInstance) {
		UE_LOG(LogTemp, Warning, TEXT("ABeltGameState::EndLevel, GameInstance is Null"));
		return;
	}
	GameInstance->SetScore(Score);
	GameInstance->SetCurrentLevelIndex(GameInstance->GetCurrentLevelIndex() + 1);
	int32 CurrentLevelIndex = GameInstance->GetCurrentLevelIndex();

	if (CurrentLevelIndex >= LevelMapNames.Num()) {
		UE_LOG(LogTemp, Warning, TEXT("ABeltGameState::EndLevel, OnGameOver, Over index"));
		OnGameOver();
		return;
	}

	if (LevelMapNames.IsValidIndex(CurrentLevelIndex)) {
		UE_LOG(LogTemp, Warning, TEXT("ABeltGameState::EndLevel, OpenLevel"));
		UGameplayStatics::OpenLevel(GetWorld(), LevelMapNames[CurrentLevelIndex]);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("ABeltGameState::EndLevel, OnGameOver Not IsValidIndex"));
		OnGameOver();
	}
}
