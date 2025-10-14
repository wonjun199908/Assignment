// Fill out your copyright notice in the Description page of Project Settings.


#include "SlowDebuffItem.h"
#include "Study/StudyCharacter.h"

void ASlowDebuffItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);

	if (AStudyCharacter* Character = Cast<AStudyCharacter>(Activator))
	{
		//Character->ActiveSlowDebuff();
	}

	DestroyItem();
}
