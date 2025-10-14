// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "HealingItem.generated.h"

/**
 * 
 */
UCLASS()
class STUDY_API AHealingItem : public ABaseItem
{
	GENERATED_BODY()
public:

	AHealingItem();

	virtual void ActivateItem(AActor* Activator) override;

	UPROPERTY(EditAnywhere, Category = "Item")
	int32 HealAmount;

};
