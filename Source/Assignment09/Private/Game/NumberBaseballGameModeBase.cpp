// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/NumberBaseballGameModeBase.h"
#include "Game/NumberBaseballGameStateBase.h"
#include "Player/NumberBaseballPlayerController.h"
#include "Player/NumberBaseballPlayerState.h"
#include "EngineUtils.h"

void ANumberBaseballGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	SecretNumberString = GenerateSecretNumber();
	UE_LOG(LogTemp, Error, TEXT("%s"), *SecretNumberString);
	CurrentPlayerIndex = 0;
	
}

void ANumberBaseballGameModeBase::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);

	ANumberBaseballPlayerController* NBPlayerController = Cast<ANumberBaseballPlayerController>(NewPlayer);
	if (NBPlayerController)
	{
		NBPlayerController->NotificationText = FText::FromString(TEXT("Connected to the game server"));
		
		AllPlayerControllers.Add(NBPlayerController);

		ANumberBaseballPlayerState* NBPlayerState = NBPlayerController->GetPlayerState<ANumberBaseballPlayerState>();
		if (NBPlayerState)
		{
			NBPlayerState->PlayerNameString = TEXT("Player") + FString::FromInt(AllPlayerControllers.Num());
		}
		
		ANumberBaseballGameStateBase* NBGameStateBase = GetGameState<ANumberBaseballGameStateBase>();
		if (NBGameStateBase)
		{
			NBGameStateBase->MulticastRPCBroadcastLoginMessage(NBPlayerState->PlayerNameString);
		}

		if (AllPlayerControllers.Num() == 2)
		{
			StartFirstTurn();
		}
	}

	
	
	
}

FString ANumberBaseballGameModeBase::GenerateSecretNumber()
{
	TArray<int32> Numbers;
	for (int32 i = 1; i <= 9; i++)
	{
		Numbers.Add(i);
	}

	FMath::RandInit(FDateTime::Now().GetTicks());
	//Numbers = Numbers.FilterByPredicate([] (int32 Num){return Num > 0;});

	FString Result;
	for (int32 i = 0; i < 3; i++)
	{
		int32 Index = FMath::RandRange(0, Numbers.Num() -1);
		Result.Append(FString::FromInt(Numbers[Index]));
		Numbers.RemoveAt(Index);
	}
	return Result;
}

bool ANumberBaseballGameModeBase::IsGuessNumberString(const FString& InNumberString)
{
	if (InNumberString.Len() != 3)
	{
		UE_LOG(LogTemp, Error, TEXT("[%s] Length %d"), *InNumberString ,InNumberString.Len());
		return false;
	}
	
	TSet<TCHAR> UniqueDigits;
	for (TCHAR C : InNumberString)
	{
		if (FChar::IsDigit(C) == false || C == '0')
		{
			return false;
		}

		UniqueDigits.Add(C);
		
	}

	if (UniqueDigits.Num() != 3)
	{
		return false;
	}
	
	return true;
}

FString ANumberBaseballGameModeBase::JudgeResult(const FString& InSecretNumberString, const FString& InGuessNumberString)
{
	int32 StrikeCount = 0;
	int32 BallCount = 0;

	for (int i = 0; i < 3; i++)
	{
		if (InSecretNumberString[i] == InGuessNumberString[i])
		{
			StrikeCount++;
		}
		else
		{
			if (InSecretNumberString.Contains(FString(1, &InGuessNumberString[i])))
			{
				BallCount++;
			}	
		}

		if (StrikeCount == 0 && BallCount == 0)
		{
			return TEXT("Out");
		}

		
	}
	return FString::Printf(TEXT("%dS%dB"),StrikeCount, BallCount); 
}

void ANumberBaseballGameModeBase::PrintChatMessageString(ANumberBaseballPlayerController* InChattingPlayerController, const FString& InChatBaseString, const FString& InChatMessageString)
{
	
	//int Index = InChatMessageString.Len() - 3;
	//FString GuessNumberString = InChatMessageString.RightChop(Index);

	
	ANumberBaseballPlayerState* NBPlayerState = InChattingPlayerController->GetPlayerState<ANumberBaseballPlayerState>();

	if (NBPlayerState)
	{
		//FString ChatMessageString = NBPlayerState->GetPlayerInfoString() + InChatMessageString;
		FString ChatMessageString;
		FString GuessNumberString = InChatMessageString;
		
		if (IsGuessNumberString(GuessNumberString))
		{
			if (NBPlayerState->bIsMyTurn == false)
			{
				FString SystemMessage = TEXT("Not your turn");
				InChattingPlayerController->ClientRPCPrintSystemMessageString(SystemMessage);

				return;
			}
			
			FString JudgeResultString = JudgeResult(SecretNumberString, GuessNumberString);
			ChangeTurn();
			//InCreaseGuessCount(InChattingPlayerController);
			ChatMessageString = NBPlayerState->GetPlayerInfoString() + InChatMessageString;
			
			for (TActorIterator<ANumberBaseballPlayerController> It(GetWorld()); It; ++It)
			{
				ANumberBaseballPlayerController* NBPlayerController = *It;
				if (NBPlayerController)
				{
					FString CombinedMessageString = ChatMessageString + TEXT(" -> ") + JudgeResultString;
					NBPlayerController->ClientRPCPrintChatMessageString(CombinedMessageString);

					int32 StrikeCount = FCString::Atoi(*JudgeResultString.Left(1));
					JudgeGame(InChattingPlayerController, StrikeCount);
					//ChangeTurn();
				}
			}
		}
		else
		{
			ChatMessageString = NBPlayerState->GetPlayerInfoString() + InChatMessageString;
			
			for (TActorIterator<ANumberBaseballPlayerController> It(GetWorld()); It; ++It)
			{
				ANumberBaseballPlayerController* NBPlayerController = *It;
				if (NBPlayerController)
				{
					NBPlayerController->ClientRPCPrintChatMessageString(ChatMessageString);
				}
			}
		}
	}
	
	
}



void ANumberBaseballGameModeBase::InCreaseGuessCount(ANumberBaseballPlayerController* InChattingPlayerController)
{
	ANumberBaseballPlayerState* NBPlayerState = InChattingPlayerController->GetPlayerState<ANumberBaseballPlayerState>();
	if (NBPlayerState)
	{
		NBPlayerState->CurrentGuessCount++;
	}
}

void ANumberBaseballGameModeBase::ResetGame()
{
	SecretNumberString = GenerateSecretNumber();

	for (const auto& PlayerController : AllPlayerControllers)
	{
		ANumberBaseballPlayerState* NBPlayerState = PlayerController->GetPlayerState<ANumberBaseballPlayerState>();
		if (NBPlayerState)
		{
			NBPlayerState->CurrentGuessCount = 0;
		}
	}
	StartFirstTurn();
}

void ANumberBaseballGameModeBase::JudgeGame(ANumberBaseballPlayerController* InChattingPlayerController, int InStrikeCount)
{
	if (InStrikeCount == 3)
	{
		ANumberBaseballPlayerState* NBPlayerState = InChattingPlayerController->GetPlayerState<ANumberBaseballPlayerState>();
		for (const auto& PlayerController : AllPlayerControllers)
		{
			if (NBPlayerState)
			{
				FString CombinedMessageString = NBPlayerState->PlayerNameString + TEXT(" has won the game");
				PlayerController->NotificationText = FText::FromString(CombinedMessageString);
				
			}
			
		}
		FTimerHandle ResetGameTimerHandle;
		GetWorldTimerManager().SetTimer(ResetGameTimerHandle, this, &ANumberBaseballGameModeBase::ResetGame, 3.f);
	}
	else
	{
		bool bIsDraw = true;
		for (const auto& PlayerController : AllPlayerControllers)
		{
			ANumberBaseballPlayerState* NBPlayerState = PlayerController->GetPlayerState<ANumberBaseballPlayerState>();
			if (NBPlayerState)
			{
				if (NBPlayerState->CurrentGuessCount < NBPlayerState->MaxGuessCount)
				{
					bIsDraw = false;
				}
				
			}
			
		}

		if (bIsDraw)
		{
			for (const auto& PlayerController : AllPlayerControllers)
			{
				PlayerController->NotificationText = FText::FromString(TEXT("Draw..."));
			}
			FTimerHandle ResetGameTimerHandle;
			GetWorldTimerManager().SetTimer(ResetGameTimerHandle, this, &ANumberBaseballGameModeBase::ResetGame, 3.f);
		}
	}
		
}

void ANumberBaseballGameModeBase::StartTurnTimer()
{
	GetWorldTimerManager().ClearTimer(TurnTimerHandle);
	Timer = 30;
	GetWorldTimerManager().SetTimer(TurnTimerHandle, this, &ANumberBaseballGameModeBase::DecreaseTurnTimer, 1.f, true);
}

void ANumberBaseballGameModeBase::DecreaseTurnTimer()
{
	
	for (const auto& PlayerController : AllPlayerControllers)
	{
		PlayerController->ClientRPCUpdateTimerWidget(Timer);
	}
	
	Timer--;
	
	if (Timer <= 0)
	{
		ChangeTurn();
	}
	
}

void ANumberBaseballGameModeBase::StartFirstTurn()
{
	ANumberBaseballPlayerState* PlayerState = AllPlayerControllers[0]->GetPlayerState<ANumberBaseballPlayerState>();
	if (PlayerState)
	{
		CurrentPlayerIndex = 0;
		PlayerState->bIsMyTurn = true;
	}
	for (const auto& PlayerController : AllPlayerControllers)
	{
		PlayerController->NotificationText = FText::FromString(TEXT("Playing NumberBaseball Game"));
	}
	StartTurnTimer();
}

void ANumberBaseballGameModeBase::ChangeTurn()
{
	StartTurnTimer();
	
	ANumberBaseballPlayerState* BeforeTurnPlayerState = AllPlayerControllers[CurrentPlayerIndex]->GetPlayerState<ANumberBaseballPlayerState>();
	InCreaseGuessCount(AllPlayerControllers[CurrentPlayerIndex]);
	if (BeforeTurnPlayerState)
	{
		BeforeTurnPlayerState->bIsMyTurn = false;
	}
	
	CurrentPlayerIndex++;

	if (CurrentPlayerIndex > AllPlayerControllers.Num()-1)
	{
		CurrentPlayerIndex = 0;
	}

	
	
	ANumberBaseballPlayerState* CurrentTurnPlayerState = AllPlayerControllers[CurrentPlayerIndex]->GetPlayerState<ANumberBaseballPlayerState>();
	if (CurrentTurnPlayerState)
	{
		CurrentTurnPlayerState->bIsMyTurn = true;
		
		for (const auto& PlayerController : AllPlayerControllers)
		{
			FString CombineString = CurrentTurnPlayerState->PlayerNameString + TEXT(" Turn");
			
			PlayerController->ClientRPCUpdateCurrentPlayerWidget(CombineString);
		}
	}
	
}


