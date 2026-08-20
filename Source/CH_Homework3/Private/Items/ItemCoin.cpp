#include "Items/ItemCoin.h"

AItemCoin::AItemCoin()
{
	Score = 10;
}

void AItemCoin::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);
	Super::ReturnToPool();
}
