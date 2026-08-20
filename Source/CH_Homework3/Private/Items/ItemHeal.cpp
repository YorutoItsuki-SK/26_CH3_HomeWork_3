#include "Items/ItemHeal.h"

AItemHeal::AItemHeal()
{
	HealAmount = 20;
}

void AItemHeal::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);
	Super::ReturnToPool();
}
