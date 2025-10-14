// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "DebuffData.h"
#include "DebuffItem.generated.h"

UCLASS()
class STUDY_API ADebuffItem : public ABaseItem
{
	GENERATED_BODY()

public:
    ADebuffItem();

protected:
	virtual void ActivateItem(AActor* Activator) override;

	UPROPERTY(EditAnywhere)
	EDebuffType DebuffType;
	
};
