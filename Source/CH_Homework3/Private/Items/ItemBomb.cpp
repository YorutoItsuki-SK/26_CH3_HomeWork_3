#include "Items/ItemBomb.h"

#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

#include "Character/BeltCharacter.h"

AItemBomb::AItemBomb()
{
	ExplosionDamage = 40;
	ItemName = TEXT("폭탄");
	ItemDesc = FString::Printf(TEXT("%d 피해를 입음"), ExplosionDamage);
}

void AItemBomb::ActivateItem(AActor* Activator)
{
	TArray<AActor*> OverlappingActors;
	CollisionActive->GetOverlappingActors(OverlappingActors);

	for (AActor* Actor : OverlappingActors) {
		if (!Actor || !Actor->ActorHasTag("Player")) {
			continue;
		}
		UGameplayStatics::ApplyDamage(
			Actor,
			ExplosionDamage,
			nullptr,
			this,
			UDamageType::StaticClass()
		);
	}
	Super::ActivateItem(Activator);
	Super::ReturnToPool();
}
