// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/NumberBaseballPlayerState.h"
#include "Player/NumberBaseballPlayerController.h"
#include "Net/UnrealNetwork.h"

ANumberBaseballPlayerState::ANumberBaseballPlayerState()
{
	bReplicates = true;

	PlayerNameString  = TEXT("None");
	CurrentGuessCount = 0;
	MaxGuessCount = 5;
	bIsMyTurn = false;
}

void ANumberBaseballPlayerState::BeginPlay()
{
	Super::BeginPlay();
	
}




void ANumberBaseballPlayerState::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, PlayerNameString);
	DOREPLIFETIME(ThisClass, CurrentGuessCount);
	DOREPLIFETIME(ThisClass, MaxGuessCount);
	DOREPLIFETIME(ThisClass, bIsMyTurn);
	
}

FString ANumberBaseballPlayerState::GetPlayerInfoString()
{
	FString PlayerInfoString = PlayerNameString + TEXT("(") + FString::FromInt(CurrentGuessCount) + TEXT("/") + FString::FromInt(MaxGuessCount) + TEXT(")");

	return PlayerInfoString;
}




