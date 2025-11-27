// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "NumberBaseballPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class ASSIGNMENT09_API ANumberBaseballPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	ANumberBaseballPlayerState();
	
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	FString GetPlayerInfoString();
	
protected:
	virtual void BeginPlay() override;
	
public:

	UPROPERTY(Replicated)
	FString PlayerNameString;

	UPROPERTY(Replicated)
	int32 CurrentGuessCount;

	UPROPERTY(Replicated)
	int32 MaxGuessCount;
	
	UPROPERTY(Replicated)
	bool bIsMyTurn;
	
	
};
