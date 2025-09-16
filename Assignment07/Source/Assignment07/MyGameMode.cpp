// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameMode.h"
#include "Bird.h"
#include "MyPlayerController.h"

AMyGameMode::AMyGameMode()
{
	DefaultPawnClass = ABird::StaticClass();
	PlayerControllerClass = AMyPlayerController::StaticClass();
}
