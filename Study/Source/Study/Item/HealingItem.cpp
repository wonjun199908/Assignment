// Fill out your copyright notice in the Description page of Project Settings.


#include "HealingItem.h"
#include "Study/StudyCharacter.h"

AHealingItem::AHealingItem()
{
	HealAmount = 20;
	ItemType = "Healing";
}

void AHealingItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);

	if (Activator && Activator->ActorHasTag("Player"))
	{
		if (AStudyCharacter* Character = Cast<AStudyCharacter>(Activator))
		{
			Character->AddHealth(HealAmount);
		}

		DestroyItem();
	}
}
