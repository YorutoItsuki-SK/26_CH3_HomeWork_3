#include "UI/PlayerUI.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

void UPlayerUI::SetScore(int32 Score)
{
	if (!TotalScoreText) {
		return;
	}
    TotalScoreText->SetText(
        FText::FromString(
            FString::Printf(
                TEXT("Score : %d"),Score
            )
        )
    );
}

void UPlayerUI::SetHealth(int32 CurrentHealth, int32 MaxHealth)
{
    if (HealthText) {
        HealthText->SetText(
            FText::FromString(
                FString::Printf(
                    TEXT("%d / %d"), 
                    CurrentHealth, MaxHealth
                ) 
            )
        );
    }

    if (HealthBar) {
        HealthBar->SetPercent(
            (float)CurrentHealth / (float)MaxHealth
        );
    }
}
