#pragma once

#include "CoreMinimal.h"
#include "Items/ItemBase.h"
#include "TableItemSpawn.generated.h"

USTRUCT(BlueprintType)
struct FTableItemSpawn : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AItemBase> ItemClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnChance;
};
