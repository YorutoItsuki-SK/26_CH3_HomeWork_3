#include "Items/ItemHeal.h"
#include "Character/BeltCharacter.h"

AItemHeal::AItemHeal()
{
	HealAmount = 20;
}

void AItemHeal::ActivateItem(AActor* Activator)
{
	ABeltCharacter* BeltCharacter = Cast<ABeltCharacter>(Activator);
	if (BeltCharacter) {
		BeltCharacter->AddHealth(HealAmount);
	}
	Super::ActivateItem(Activator);
	Super::ReturnToPool();
}
