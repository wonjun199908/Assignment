// Copyright Epic Games, Inc. All Rights Reserved.

#include "Assignment06GameMode.h"
#include "Assignment06Character.h"
#include "UObject/ConstructorHelpers.h"

AAssignment06GameMode::AAssignment06GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
