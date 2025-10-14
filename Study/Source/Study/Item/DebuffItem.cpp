// Fill out your copyright notice in the Description page of Project Settings.


#include "DebuffItem.h"
#include "Study/StudyCharacter.h"

ADebuffItem::ADebuffItem()
{
	DebuffType = EDebuffType::Slow;
}

void ADebuffItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);

	if (AStudyCharacter* Character = Cast<AStudyCharacter>(Activator))
	{
		Character->ActiveDebuff(DebuffType);
	}

	DestroyItem();

}
