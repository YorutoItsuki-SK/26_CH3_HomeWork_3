#include "Items/ItemHeal.h"
#include "Character/BeltCharacter.h"

AItemHeal::AItemHeal()
{
	HealAmount = 20;
	ItemName = TEXT("회복약");
	ItemDesc = FString::Printf(TEXT("%d 체력 회복"), HealAmount);
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
