// Fill out your copyright notice in the Description page of Project Settings.


#include "StudyGameInstance.h"

UStudyGameInstance::UStudyGameInstance()
{
	TotalScore = 0;
	CurrentLevelIndex = 0;
}

void UStudyGameInstance::AddToScore(int32 Amount)
{
	TotalScore += Amount;
}


