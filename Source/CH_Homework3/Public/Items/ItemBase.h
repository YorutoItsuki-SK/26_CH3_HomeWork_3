#pragma once

#include "CoreMinimal.h"
#include "System/PoolingObject.h"
#include "ItemBase.generated.h"

class USphereComponent;
class UWidgetComponent;

UCLASS()
class CH_HOMEWORK3_API AItemBase : public APoolingObject
{
	GENERATED_BODY()

public:
	AItemBase();

	virtual void ActivateItem(AActor* Activator);

	virtual void Deploy(FVector Location, FRotator Rotate);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Component")
	USceneComponent* Scene;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Component")
	UStaticMeshComponent* StaticMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Component")
	USphereComponent* CollisionActive;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Component")
	USphereComponent* CollisionUi;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Effect")
	USoundBase* PickupSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Effect")
	UParticleSystem* Particle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Effect")
	UWidgetComponent* ItemWidget;

	bool bIsActivated = false;

	virtual void OnOverlapStartWidget(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);
	virtual void OnOverlapEndWidget(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex
	);
	virtual void OnOverlapStartActive(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);
	virtual void OnOverlapEndActive(
		UPrimitiveComponent* OverLappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex
	);
	

};
