// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TimerWidget.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class ASSIGNMENT09_API UTimerWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TimerTextBlock;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> CurrentTurnTextBlock;

	
	void UpdateTimerText(int Time);
	void UpdateCurrentPlayer(FString PlayerName);
};
