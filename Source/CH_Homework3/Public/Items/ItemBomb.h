#pragma once

#include "CoreMinimal.h"
#include "Items/ItemBase.h"
#include "ItemBomb.generated.h"

UCLASS()
class CH_HOMEWORK3_API AItemBomb : public AItemBase
{
	GENERATED_BODY()

public:
	AItemBomb();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Explosion")
	int32 ExplosionDamage;
	
	virtual void ActivateItem(AActor* Activator) override;
};
