// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/ItemBase.h"
#include "ItemCoin.generated.h"

/**
 * 
 */
UCLASS()
class CH_HOMEWORK3_API AItemCoin : public AItemBase
{
	GENERATED_BODY()

public:
	AItemCoin();
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="GameData")
	int32 Score;

	virtual void ActivateItem(AActor* Activator) override;
};
