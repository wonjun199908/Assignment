// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TimerWidget.h"

#include <string>

#include "Components/TextBlock.h"
#include "Player/NumberBaseballPlayerState.h"

void UTimerWidget::UpdateTimerText(int Time)
{
	FString TimeToString = FString::Printf(TEXT("%d"), Time);
	TimerTextBlock->SetText(FText::FromString(TimeToString));
}

void UTimerWidget::UpdateCurrentPlayer(FString PlayerName)
{
	CurrentTurnTextBlock->SetText(FText::FromString(PlayerName));
}


