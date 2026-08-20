#include "Items/ItemBomb.h"

AItemBomb::AItemBomb()
{
	ExplosionDamage = 40;
}

void AItemBomb::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);
	Super::ReturnToPool();
}
