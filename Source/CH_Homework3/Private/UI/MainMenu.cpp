#include "UI/MainMenu.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/StackBox.h"
#include "Kismet/KismetSystemLibrary.h"

#include "BeltGameState.h"

void UMainMenu::SetBoxScoreShow(bool bIsShow)
{
	if (BoxScore) {
		if (bIsShow) {
			BoxScore->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		}
		else {
			BoxScore->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}

void UMainMenu::SetBoxStartShow(bool bIsShow)
{
	if (BoxStart) {
		if (bIsShow) {
			BoxStart->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		}
		else {
			BoxStart->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}

void UMainMenu::SetMenuText(FString NewMenuText)
{
	if (MenuText) {
		MenuText->SetText(
			FText::FromString(
				NewMenuText
			)
		);
	}
}

void UMainMenu::SetScoreText(FString NewScoreText)
{
	if (ScoreText) {
		ScoreText->SetText(
			FText::FromString(
				NewScoreText
			)
		);
	}
}

void UMainMenu::NativeConstruct() 
{
	Super::NativeConstruct();

	if (ButtonStart) {
		ButtonStart->OnClicked.AddDynamic(
			this,
			&UMainMenu::OnButtonStartClicked
		);
	}

	if (ButtonEnd) {
		ButtonEnd->OnClicked.AddDynamic(
			this,
			&UMainMenu::OnButtonEndClicked
		);
	}
}

void UMainMenu::OnButtonStartClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("UMainMenu::OnButtonStartClicked"));
	ABeltGameState* BeltGameState = Cast<ABeltGameState>(GetWorld()->GetGameState());
	if (!BeltGameState) {
		UE_LOG(LogTemp, Warning, TEXT("UMainMenu::OnButtonStartClicked, BeltGameState is Null"));
		return;
	}
	BeltGameState->EndLevel();
}

void UMainMenu::OnButtonEndClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("UMainMenu::OnButtonEndClicked"));
	UWorld* World = GetWorld();
	if (!World) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();

	UKismetSystemLibrary::QuitGame(
		World,
		PlayerController,
		EQuitPreference::Quit,
		false
	);
}
