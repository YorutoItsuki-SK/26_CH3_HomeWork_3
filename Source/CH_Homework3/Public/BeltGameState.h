#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "BeltGameState.generated.h"

UCLASS()
class CH_HOMEWORK3_API ABeltGameState : public AGameState
{
	GENERATED_BODY()
	
public:
	ABeltGameState();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintPure, Category = "Score")
	int32 GetScore() const;
	UFUNCTION(BlueprintCallable, Category = "Score")
	void AddScore(int32 Amount);

	void UpdateHUD();

	UFUNCTION(BlueprintCallable, Category = "Level")
	void OnGameOver();
	UFUNCTION(BlueprintCallable, Category = "Level")
	UDataTable* GetWaveData() const;
	UFUNCTION(BlueprintCallable, Category = "Level")
	void EndLevel();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Score")
	int32 Score;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level")
	TArray<FName> LevelMapNames;

};
