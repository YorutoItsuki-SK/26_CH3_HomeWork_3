#pragma once

#include "CoreMinimal.h"
#include "TableWave.generated.h"

USTRUCT(BlueprintType)
struct FTableWave : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float WaveTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SpawnCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BeltSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnFrequency;
};
