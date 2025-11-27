// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/NumberBaseballGameStateBase.h"

#include "Kismet/GameplayStatics.h"
#include "Player/NumberBaseballPlayerController.h"

void ANumberBaseballGameStateBase::MulticastRPCBroadcastLoginMessage_Implementation(const FString& InNameString)
{
	if (!HasAuthority())
	{
		ANumberBaseballPlayerController* NumberBaseballPlayerController = Cast<ANumberBaseballPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

		if (NumberBaseballPlayerController)
		{
			FString NotificationString = InNameString +	TEXT(" has join the game");
			NumberBaseballPlayerController->PrintChatMessageString(NotificationString);
		}
	}
	
}
