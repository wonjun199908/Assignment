// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DebuffItem.h"
#include "SlowDebuffItem.generated.h"

/**
 * 
 */
UCLASS()
class STUDY_API ASlowDebuffItem : public ADebuffItem
{
	GENERATED_BODY()
	
protected:

	virtual void ActivateItem(AActor* Activator) override;

};
