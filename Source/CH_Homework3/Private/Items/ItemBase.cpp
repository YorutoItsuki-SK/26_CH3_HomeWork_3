#include "Items/ItemBase.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"

AItemBase::AItemBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(Scene);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(Scene);

	CollisionActive = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionActive"));
	CollisionActive->SetupAttachment(Scene);
	CollisionActive->OnComponentBeginOverlap.AddDynamic(this, &AItemBase::OnOverlapStartActive);
	CollisionActive->OnComponentEndOverlap.AddDynamic(this, &AItemBase::OnOverlapEndActive);

	CollisionUi = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionUi"));
	CollisionUi->SetupAttachment(Scene);
	CollisionUi->OnComponentBeginOverlap.AddDynamic(this, &AItemBase::OnOverlapStartWidget);
	CollisionUi->OnComponentEndOverlap.AddDynamic(this, &AItemBase::OnOverlapEndWidget);
	CollisionUi->InitSphereRadius(300.f);

	ItemWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	ItemWidget->SetVisibility(false);
	ItemWidget->SetupAttachment(Scene);
}

void AItemBase::ActivateItem(AActor* Activator)
{
	bIsActivated = true;
}

void AItemBase::Deploy(FVector Location, FRotator Rotate)
{
	SetActorLocationAndRotation(Location, Rotate);
	bIsActivated = false;
	Super::OnAcquire();
}

void AItemBase::OnOverlapStartWidget(
	UPrimitiveComponent* OverlappedComp, 
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, 
	bool bFromSweep, 
	const FHitResult& SweepResult)
{
	if (!OtherActor || !OtherActor->ActorHasTag("Player")) return;

	if (ItemWidget) {
		ItemWidget->SetVisibility(true);
	}
}

void AItemBase::OnOverlapEndWidget(
	UPrimitiveComponent* OverlappedComp, 
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex)
{
	if (!OtherActor || !OtherActor->ActorHasTag("Player")) return;

	if (ItemWidget) {
		ItemWidget->SetVisibility(false);
	}
}

void AItemBase::OnOverlapStartActive(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, 
	bool bFromSweep, 
	const FHitResult& SweepResult)
{
	if (!OtherActor || !OtherActor->ActorHasTag("Player")) return;
	if (bIsActivated) return;
	bIsActivated = true;
	ActivateItem(OtherActor);
}

void AItemBase::OnOverlapEndActive(
	UPrimitiveComponent* OverLappedComp, 
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex)
{
}
