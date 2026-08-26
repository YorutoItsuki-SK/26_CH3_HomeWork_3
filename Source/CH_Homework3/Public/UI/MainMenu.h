#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

class UButton;
class UTextBlock;
class UStackBox;

UCLASS()
class CH_HOMEWORK3_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

public:
    UFUNCTION()
    void SetBoxScoreShow(bool bIsShow);
    UFUNCTION()
    void SetBoxStartShow(bool bIsShow);
    UFUNCTION()
    void SetMenuText(FString NewMenuText);
    UFUNCTION()
    void SetScoreText(FString NewScoreText);

protected:

    virtual void NativeConstruct() override;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UStackBox> BoxScore;
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UStackBox> BoxStart;
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> ButtonStart; 
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> ButtonEnd;
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> ScoreText;
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> MenuText;

    UFUNCTION()
    void OnButtonStartClicked();
    UFUNCTION()
    void OnButtonEndClicked();
};
