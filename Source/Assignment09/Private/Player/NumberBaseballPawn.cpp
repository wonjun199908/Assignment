// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/NumberBaseballPawn.h"

#include "Assignment09/Assignment09.h"

// Sets default values
ANumberBaseballPawn::ANumberBaseballPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANumberBaseballPawn::BeginPlay()
{
	Super::BeginPlay();

	FString NetModeString = NumberBaseballFunctionLibrary::GetRoleString(this);
	//FString CombinedString = FString::Printf(TEXT("NumberBaseballPawn::BeginPlay() %s [%s]"), NumberBaseballFunctionLibrary::GetNetModeString())
	
}

void ANumberBaseballPawn::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}



