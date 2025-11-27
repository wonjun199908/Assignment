// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NumberBaseballGameModeBase.generated.h"

class ANumberBaseballPlayerController;
/**
 * 
 */
UCLASS()
class ASSIGNMENT09_API ANumberBaseballGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:

	virtual  void BeginPlay() override;
	
	virtual void OnPostLogin(AController* NewPlayer) override;

	FString GenerateSecretNumber();

	bool IsGuessNumberString(const FString& InNumberString);

	FString JudgeResult(const FString& InSecretNumberString, const FString& InGuessNumberString);

	void PrintChatMessageString(ANumberBaseballPlayerController* InChattingPlayerController, const FString& InChatBaseString, const FString& InChatMessageString);
	void InCreaseGuessCount(ANumberBaseballPlayerController* InChattingPlayerController);
	
	void ResetGame();

	void JudgeGame(ANumberBaseballPlayerController* InChattingPlayerController, int InStrikeCount);

	void StartTurnTimer();
	void DecreaseTurnTimer();
	void StartFirstTurn();
	void ChangeTurn();
	
	int Timer;
	int CurrentPlayerIndex;
	FTimerHandle TurnTimerHandle;
	

	
protected:
	FString SecretNumberString;

	TArray<TObjectPtr<ANumberBaseballPlayerController>> AllPlayerControllers;
};
