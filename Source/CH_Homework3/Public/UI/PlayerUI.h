#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerUI.generated.h"

class UTextBlock;
class UProgressBar;

UCLASS()
class CH_HOMEWORK3_API UPlayerUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "UI|Score")
	void SetScore(int32 Score);
	UFUNCTION(BlueprintCallable, Category = "UI|Health")
	void SetHealth(int32 CurrentHealth, int32 MaxHealth);
	
protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> HealthText;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> HealthBar;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TotalScoreText;
};
