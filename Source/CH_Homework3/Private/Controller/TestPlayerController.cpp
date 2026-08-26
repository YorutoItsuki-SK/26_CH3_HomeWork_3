#include "Controller/TestPlayerController.h"

#include "EnhancedInputSubsystems.h"

#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

#include "BeltGameState.h"
#include "BeltGameInstance.h"
#include "UI/MainMenu.h"

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

	bShowMouseCursor = false;
	SetInputMode(FInputModeGameOnly());

	FString CurrentMapName = GetWorld()->GetMapName();
	UE_LOG(LogTemp, Warning, TEXT("ATestPlayerController::BeginPlay, CurrentMapName : %s"), *CurrentMapName);
	if (CurrentMapName.Contains("MainMenu")) {
		UE_LOG(LogTemp, Warning, TEXT("ATestPlayerController::BeginPlay, MainMenu"));
		ShowMainMenu(false);
	}
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

void ATestPlayerController::ShowMainMenu(bool bIsDead)
{
	if (!MainMenuWidgetClass) {
		UE_LOG(LogTemp, Warning, TEXT("ATestPlayerController::ShowMainMenu, MainMenuWidgetClass is Null"));
		return;
	}
	if (MainMenuWidgetClass) {
		MainMenuWidgetClass->RemoveFromParent();
	}

	MainMenuWidgetClass->AddToViewport();

	UBeltGameInstance* GameInstance = Cast<UBeltGameInstance>(UGameplayStatics::GetGameInstance(this));
	if (!GameInstance) {
		UE_LOG(LogTemp, Warning, TEXT("ATestPlayerController::ShowMainMenu, UBeltGameInstance is Null"));
		return;
	}
	ABeltGameState* GameState = GetWorld() ? GetWorld()->GetGameState<ABeltGameState>() : nullptr;
	if (!GameState) {
		UE_LOG(LogTemp, Warning, TEXT("ATestPlayerController::ShowMainMenu, GameState is Null"));
		return;
	}
	if (GameInstance->GetCurrentLevelIndex() == 0) {
		MainMenuWidgetClass->SetBoxScoreShow(false);
	}
	else {
		MainMenuWidgetClass->SetBoxScoreShow(true);
		MainMenuWidgetClass->SetScoreText(FString::Printf(TEXT("Score : %d"), GameState->GetScore()));
	}

	if (bIsDead) {
		MainMenuWidgetClass->SetBoxStartShow(false);
	}
	else {
		if (GameInstance->GetCurrentLevelIndex() == 0) {
			UE_LOG(LogTemp, Warning, TEXT("ATestPlayerController::ShowMainMenu, Start"));
			MainMenuWidgetClass->SetBoxStartShow(true);
			MainMenuWidgetClass->SetMenuText(FString(TEXT("게임 시작")));
		}
		else if (GameInstance->HasMoreLevel()) {
			UE_LOG(LogTemp, Warning, TEXT("ATestPlayerController::ShowMainMenu, HasMoreLevel"));
			MainMenuWidgetClass->SetBoxStartShow(true);
			MainMenuWidgetClass->SetMenuText(FString(TEXT("다음 레벨")));
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("ATestPlayerController::ShowMainMenu, End"));
			MainMenuWidgetClass->SetBoxStartShow(false);
		}
	}

	bShowMouseCursor = true;
	SetInputMode(FInputModeUIOnly());
}
