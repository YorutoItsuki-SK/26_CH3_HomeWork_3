// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/ItemBase.h"
#include "ItemHeal.generated.h"

/**
 * 
 */
UCLASS()
class CH_HOMEWORK3_API AItemHeal : public AItemBase
{
	GENERATED_BODY()
public:
	AItemHeal();
protected:
	UPROPERTY(EditAnywhere, Category = "Item|Heal")
	int32 HealAmount;

	virtual void ActivateItem(AActor* Activator) override;
};
