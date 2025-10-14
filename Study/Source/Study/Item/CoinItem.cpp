// Fill out your copyright notice in the Description page of Project Settings.


#include "CoinItem.h"
#include "Study/StudyGameState.h"

ACoinItem::ACoinItem()
{
	PointValue = 0;
	ItemType = "DefaultCoin";
}

void ACoinItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);


	if (Activator && Activator->ActorHasTag("Player"))
	{
		if (UWorld* World = GetWorld())
		{
			if(AStudyGameState* GameState = World->GetGameState<AStudyGameState>())
			{
				GameState->AddScore(PointValue);
				GameState->OnCoinCollected();
				
			}
		}

		DestroyItem();
	}
}

