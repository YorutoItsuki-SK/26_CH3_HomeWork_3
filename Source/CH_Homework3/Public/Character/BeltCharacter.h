#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BeltCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UWidgetComponent;
struct FInputActionValue;

UCLASS()
class CH_HOMEWORK3_API ABeltCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABeltCharacter();

protected:
	float NormalSpeed;
	float SprintSpeedMultiplier;
	float SprintSpeed;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	int32 MaxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	int32 Health;

	virtual float TakeDamage(
		float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		AController* EventInstigator,
		AActor* DamageCauser
	) override;

	virtual void BeginPlay() override;

	UFUNCTION()
	void Move(const FInputActionValue& value);
	UFUNCTION()
	void Look(const FInputActionValue& value);

	void OnDeath();

	void UpdateOverheadHP();

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	UWidgetComponent* OverheadWidget;

	UFUNCTION(BlueprintPure, Category = "Health")
	int32 GetHeath() const;
	UFUNCTION(BlueprintCallable, Category = "Health")
	void AddHealth(int32 Amount);

	UFUNCTION()
	void UpdateOverheadScore();
};
