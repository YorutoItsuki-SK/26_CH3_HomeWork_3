#include "Controller/TestPlayerController.h"

#include "EnhancedInputSubsystems.h"

#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

#include "BeltGameState.h"
#include "BeltGameInstance.h"

ATestPlayerController::ATestPlayerController():
	InputMappingContext(nullptr),
	MoveAction(nullptr),
	LookAction(nullptr),
	HUDWidgetClass(nullptr),
	HUDWidgetInstance(nullptr),
	MainMenuWidgetClass(nullptr),
	MainMenuWidgetInstance(nullptr)
{
}

void ATestPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ULocalPlayer* LocalPlayer = GetLocalPlayer();
	if (!LocalPlayer) {
		return;
	}
	UEnhancedInputLocalPlayerSubsystem* PlayerSubSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	if (!PlayerSubSystem) {
		return;
	}
	
	if (!InputMappingContext) {
		return;
	}
	PlayerSubSystem->AddMappingContext(InputMappingContext, 0);

}

UUserWidget* ATestPlayerController::GetHUDWidget() const
{
	return HUDWidgetInstance;
}

void ATestPlayerController::ShowGameHud()
{
	if (HUDWidgetInstance) {
		HUDWidgetInstance->RemoveFromParent();
		HUDWidgetInstance = nullptr;
	}

	if (MainMenuWidgetInstance) {
		MainMenuWidgetInstance->RemoveFromParent();
		MainMenuWidgetInstance = nullptr;
	}

	if (!HUDWidgetClass) {
		return;
	}
	HUDWidgetInstance = CreateWidget<UUserWidget>(this, HUDWidgetClass);
	if (!HUDWidgetInstance) {
		return;
	}
	HUDWidgetInstance->AddToViewport();
	bShowMouseCursor = false;
	SetInputMode(FInputModeGameOnly());

	ABeltGameState* GameState = GetWorld() ? GetWorld()->GetGameState<ABeltGameState>() : nullptr;
	if (!GameState) {
		return;
	}
	GameState->UpdateHUD();
}

void ATestPlayerController::ShowMainMenu(bool bIsRestart)
{
	if (HUDWidgetInstance) {
		HUDWidgetInstance->RemoveFromParent();
		HUDWidgetInstance = nullptr;
	}

	if (MainMenuWidgetInstance) {
		MainMenuWidgetInstance->RemoveFromParent();
		MainMenuWidgetInstance = nullptr;
	}

	if (!MainMenuWidgetClass) {
		return;
	}
	MainMenuWidgetInstance = CreateWidget<UUserWidget>(this, MainMenuWidgetClass);
	if (!MainMenuWidgetInstance) {
		return;
	}
	MainMenuWidgetInstance->AddToViewport();
	bShowMouseCursor = true;
	SetInputMode(FInputModeUIOnly());

	UTextBlock* ButtonText = Cast<UTextBlock>(MainMenuWidgetInstance->GetWidgetFromName(TEXT("StartButtonText")));
	if (!ButtonText) {
		return;
	}
	if (bIsRestart) {
		ButtonText->SetText(FText::FromString(TEXT("Restart")));
	}
	else {
		ButtonText->SetText(FText::FromString(TEXT("Start")));
	}

	if (bIsRestart) {
		UFunction* PlayAnimFunc = MainMenuWidgetInstance->FindFunction(FName("PlayGameOverAnim"));
		if (!PlayAnimFunc) {
			return;
		}
		MainMenuWidgetInstance->ProcessEvent(PlayAnimFunc, nullptr);

		UTextBlock* TotalScoreText = Cast<UTextBlock>(MainMenuWidgetInstance->GetWidgetFromName("TotalScoreText"));
		if (!TotalScoreText) {
			return;
		}
		UBeltGameInstance* GameInstance = Cast<UBeltGameInstance>(UGameplayStatics::GetGameInstance(this));
		if (!GameInstance) {
			return;
		}
		TotalScoreText->SetText(
			FText::FromString(FString::Printf(TEXT("Total Score : %d"), GameInstance->GetScore()))
		);
	}
}
