#include "Items/ItemBomb.h"

#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

#include "Character/BeltCharacter.h"

AItemBomb::AItemBomb()
{
	ExplosionDamage = 40;
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
