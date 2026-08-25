#include "Character/BeltCharacter.h"

#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Components/TextBlock.h"
#include "Components/WidgetComponent.h"

#include "Controller/TestPlayerController.h"
#include "Camera/CameraComponent.h"

#include "EnhancedInputComponent.h"
#include "BeltGameState.h"


// Sets default values
ABeltCharacter::ABeltCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength = 300.f;
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
	CameraComp->bUsePawnControlRotation = false;

	OverheadWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("OverheadWidget"));
	OverheadWidget->SetupAttachment(GetMesh());
	OverheadWidget->SetWidgetSpace(EWidgetSpace::Screen);

	NormalSpeed = 600.f;
	SprintSpeedMultiplier = 1.7f;
	SprintSpeed = NormalSpeed * SprintSpeedMultiplier;

	GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;

	MaxHealth = 100;
	Health = MaxHealth;

}

float ABeltCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Health = FMath::Clamp(Health - DamageAmount, 0, MaxHealth);

	UpdateOverheadHP();

	if (Health <= 0) {
		OnDeath();
	}

	return DamageAmount;
}

int32 ABeltCharacter::GetHeath() const
{
	return Health;
}

void ABeltCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABeltCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABeltCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhacedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (!EnhacedInput) {
		return;
	}

	ATestPlayerController* PlayerController = Cast<ATestPlayerController>(GetController());
	if (!PlayerController) {
		return;
	}

	if (PlayerController->MoveAction) {
		EnhacedInput->BindAction(
			PlayerController->MoveAction,
			ETriggerEvent::Triggered,
			this,
			&ABeltCharacter::Move
		);
	}

	if (PlayerController->LookAction) {
		EnhacedInput->BindAction(
			PlayerController->LookAction,
			ETriggerEvent::Triggered,
			this,
			&ABeltCharacter::Look
		);
	}
}

void ABeltCharacter::Move(const FInputActionValue& value)
{
	if (!Controller) return;

	const FVector2D MoveInput = value.Get<FVector2D>();

	if (!FMath::IsNearlyZero(MoveInput.X)) {
		AddMovementInput(GetActorForwardVector(), MoveInput.X);
	}

	if (!FMath::IsNearlyZero(MoveInput.Y)) {
		AddMovementInput(GetActorRightVector(), MoveInput.Y);
	}

}

void ABeltCharacter::Look(const FInputActionValue& value)
{
	FVector2D LookInput = value.Get<FVector2D>();

	AddControllerYawInput(LookInput.X);
	AddControllerPitchInput(LookInput.Y);
}

void ABeltCharacter::OnDeath()
{
	ABeltGameState* BeltGameState = GetWorld() ? GetWorld()->GetGameState<ABeltGameState>() : nullptr;
	if (!BeltGameState) {
		return;
	}
	BeltGameState->OnGameOver();
}

void ABeltCharacter::UpdateOverheadHP()
{
	if (!OverheadWidget) return;

	UUserWidget* OverheadWidgetInstance = OverheadWidget->GetUserWidgetObject();
	if (!OverheadWidgetInstance) return;

	UTextBlock* HPText = Cast<UTextBlock>(OverheadWidgetInstance->GetWidgetFromName(TEXT("OverheadHP")));
	if (!HPText) {
		return;
	}
	HPText->SetText(FText::FromString(FString::Printf(TEXT("%d / %d"), Health, MaxHealth)));

}


void ABeltCharacter::AddHealth(int32 Amount)
{
	if (Amount < 0) {
		return;
	}
	Health = FMath::Clamp(Health + Amount, 0, MaxHealth);
}