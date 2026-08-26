#include "Items/ItemBase.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Spawner/ItemSpawnVolume.h"
#include "BeltGameMode.h"

AItemBase::AItemBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(Scene);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(Scene);

	CollisionActive = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionActive"));
	CollisionActive->SetupAttachment(Scene);

	CollisionUi = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionUi"));
	CollisionUi->SetupAttachment(Scene);
	CollisionUi->InitSphereRadius(300.f);

	ItemWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	ItemWidget->SetVisibility(false);
	ItemWidget->SetupAttachment(Scene);

	ItemName = TEXT("기본 아이템 이름");
	ItemDesc = TEXT("기본 아이템 설명");
}

void AItemBase::ActivateItem(AActor* Activator)
{
	bIsActivated = true;
	if (PickupSound) {
		UGameplayStatics::PlaySoundAtLocation(
			GetWorld(),
			PickupSound,
			GetActorLocation()
		);
	}
}

void AItemBase::Deploy(FVector Location)
{
	SetActorLocation(Location);
	bIsActivated = false;
	Super::OnAcquire();
}

void AItemBase::MoveX(float DeltaSpeed)
{
	FVector CurrentLocation = GetActorLocation();
	SetActorLocation(
		FVector(
			CurrentLocation.X + DeltaSpeed,
			CurrentLocation.Y,
			CurrentLocation.Z
		)
	);
}

void AItemBase::SetSpawner(AItemSpawnVolume* NewItemSpawnVolume)
{
	Spawner = NewItemSpawnVolume;
}

void AItemBase::BeginPlay()
{
	Super::BeginPlay();
	CollisionActive->OnComponentBeginOverlap.AddDynamic(this, &AItemBase::OnOverlapStartActive);
	CollisionActive->OnComponentEndOverlap.AddDynamic(this, &AItemBase::OnOverlapEndActive);
	CollisionUi->OnComponentBeginOverlap.AddDynamic(this, &AItemBase::OnOverlapStartWidget);
	CollisionUi->OnComponentEndOverlap.AddDynamic(this, &AItemBase::OnOverlapEndWidget);

	if (UUserWidget* ItemWidgetInstance = ItemWidget->GetUserWidgetObject()) {
		UTextBlock* ItemNameText = Cast<UTextBlock>(ItemWidgetInstance->GetWidgetFromName(TEXT("ItemNameText")));
		if (ItemNameText) {
			ItemNameText->SetText(FText::FromString(ItemName));
		}
		UTextBlock* ItemDescText = Cast<UTextBlock>(ItemWidgetInstance->GetWidgetFromName(TEXT("ItemDescText")));
		if (ItemDescText) {
			ItemDescText->SetText(FText::FromString(ItemDesc));
		}
	}
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
	if (bIsActivated) {
		UE_LOG(LogTemp, Warning, TEXT("AItemBase::OnOverlapStartActive, Activate : True"));
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("AItemBase::OnOverlapStartActive, Activate : False"));
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

void AItemBase::ReturnToPool()
{
	if (Spawner.IsValid()) {
		Spawner.Get()->ReportDespawn(this);
	}

	ABeltGameMode* GameMode = Cast<ABeltGameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode) {
		GameMode->ItemDespawned();
	}

	Super::ReturnToPool();
}
