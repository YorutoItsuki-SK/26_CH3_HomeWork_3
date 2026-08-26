#include "BeltGameInstance.h"

UBeltGameInstance::UBeltGameInstance()
{
	TotalScore = 0;
	CurrentLevelIndex = 0;
}

void UBeltGameInstance::SetScore(int32 Amount)
{
	TotalScore += Amount;
}

void UBeltGameInstance::SetCurrentLevelIndex(int32 NewLevelIndex)
{
	CurrentLevelIndex = NewLevelIndex;
}

int32 UBeltGameInstance::GetScore() const
{
	return TotalScore;
}

int32 UBeltGameInstance::GetCurrentLevelIndex() const
{
	return CurrentLevelIndex;
}

void UBeltGameInstance::ResetAllValue()
{
	TotalScore = 0;
	CurrentLevelIndex = 0;
}

UDataTable* UBeltGameInstance::GetTableWave() const
{
	if (TableWaves.IsEmpty()) {
		UE_LOG(LogTemp, Warning, TEXT("UBeltGameInstance::GetTableWave is Empty"));
		return nullptr;
	}
	if (TableWaves.IsValidIndex(CurrentLevelIndex)) {
		return TableWaves[CurrentLevelIndex];
	}
	UE_LOG(LogTemp, Warning, TEXT("UBeltGameInstance::GetTableWave is Null"));
	return nullptr;
}

bool UBeltGameInstance::HasMoreLevel() const
{
	if (CurrentLevelIndex >= TableWaves.Num()) {
		return false;
	}
	else {
		return true;
	}
}
