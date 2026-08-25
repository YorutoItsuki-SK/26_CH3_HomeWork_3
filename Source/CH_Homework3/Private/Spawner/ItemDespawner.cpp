#include "Spawner/ItemDespawner.h"

#include "Components/BoxComponent.h"

#include "Items/ItemBase.h"

// Sets default values
AItemDespawner::AItemDespawner()
{
	PrimaryActorTick.bCanEverTick = false;
	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(Scene);
	DeSpawningBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	DeSpawningBox->SetupAttachment(Scene);

}

void AItemDespawner::BeginPlay()
{
	Super::BeginPlay();
	DeSpawningBox->OnComponentBeginOverlap.AddDynamic(this, &AItemDespawner::OnOverlapStart);
	
}

void AItemDespawner::DeSpawnItem(AItemBase* TriggeredItem)
{
	if (!TriggeredItem) {
		return;
	}
	TriggeredItem->ReturnToPool();
}

void AItemDespawner::OnOverlapStart(
	UPrimitiveComponent* OverlappedComp, 
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, 
	bool bFromSweep, 
	const FHitResult& SweepResult)
{
	if (!OtherActor) {
		return;
	}
	DeSpawnItem(Cast<AItemBase>(OtherActor));
}

