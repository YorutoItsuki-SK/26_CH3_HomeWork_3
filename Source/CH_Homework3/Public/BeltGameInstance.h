#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BeltGameInstance.generated.h"

UCLASS()
class CH_HOMEWORK3_API UBeltGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UBeltGameInstance();

	UFUNCTION(BlueprintCallable, Category = "GameData")
	void AddToScore(int32 Amount);
	UFUNCTION(BlueprintCallable, Category = "GameData")
	void SetCurrentLevelIndex(int32 NewLevelIndex);
	UFUNCTION(BlueprintCallable, Category = "GameData")
	int32 GetScore() const;
	UFUNCTION(BlueprintCallable, Category = "GameData")
	int32 GetCurrentLevelIndex() const;
	UFUNCTION(BlueprintCallable, Category = "GameData")
	void ResetAllValue();
	UFUNCTION(BlueprintCallable, Category = "GameData")
	UDataTable* GetTableWave() const;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GameData")
	int32 TotalScore;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GameData")
	int32 CurrentLevelIndex;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameData")
	TArray<UDataTable*> TableWaves;
	
};
