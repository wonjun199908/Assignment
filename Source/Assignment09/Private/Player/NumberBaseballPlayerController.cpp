// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/NumberBaseballPlayerController.h"

#include "Assignment09/Assignment09.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UI/ChatInput.h"
#include "EngineUtils.h"
#include "Game/NumberBaseballGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Player/NumberBaseballPlayerState.h"
#include "UI/TimerWidget.h"

ANumberBaseballPlayerController::ANumberBaseballPlayerController()
{
	bReplicates = true;
}



void ANumberBaseballPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalController() == false)
	{
		return;
	}
	
	FInputModeUIOnly InputModeUIOnly;
	SetInputMode(InputModeUIOnly);
	
	if (ChatInputWidgetClass)
	{
		ChatInputWidgetInstance = CreateWidget<UChatInput>(this, ChatInputWidgetClass);

		if (ChatInputWidgetInstance)
		{
			ChatInputWidgetInstance->AddToViewport();
		}
	}

	if (NotificationTextWidgetClass)
	{
		NotificationTextWidgetInstance = CreateWidget<UUserWidget>(this, NotificationTextWidgetClass);

		if (NotificationTextWidgetInstance)
		{
			NotificationTextWidgetInstance->AddToViewport();
		}
	}

	if (TimerWidgetClass)
	{
		TimerWidgetInstance = CreateWidget<UTimerWidget>(this, TimerWidgetClass);
		if (TimerWidgetInstance)
		{
			TimerWidgetInstance->AddToViewport();
		}
	}
}


void ANumberBaseballPlayerController::SetChatMessageString(const FString& InChatMessageString)
{
	ChatMessageString = InChatMessageString;

	if (IsLocalController())
	{
		ANumberBaseballPlayerState* NBPlayerState = GetPlayerState<ANumberBaseballPlayerState>();
		if (NBPlayerState)
		{
			FString CombinedMessageString = NBPlayerState->GetPlayerInfoString() + TEXT(": ");
			ServerRPCPrintChatMessageString(CombinedMessageString, InChatMessageString);
		}
	}
}

void ANumberBaseballPlayerController::PrintChatMessageString(const FString& InChatMessageString)
{
	NumberBaseballFunctionLibrary::MyPrintString(this, InChatMessageString, 3.f);
}

void ANumberBaseballPlayerController::PrintSystemMessageString(const FString& InChatMessageString)
{
	NumberBaseballFunctionLibrary::MyPrintString(this, InChatMessageString, 3.f, FColor::Red);
}


void ANumberBaseballPlayerController::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, NotificationText);
}

void ANumberBaseballPlayerController::ClientRPCPrintChatMessageString_Implementation(const FString& InChatMessageString)
{
	PrintChatMessageString(InChatMessageString);
}

void ANumberBaseballPlayerController::ServerRPCPrintChatMessageString_Implementation(const FString& InChatBaseString, const FString& InChatMessageString)
{
	// for (TActorIterator<ANumberBaseballPlayerController> It(GetWorld()); It; ++It)
	// {
	// 	ANumberBaseballPlayerController* PlayerController = *It;
	// 	if (PlayerController)
	// 	{
	// 		PlayerController->ClientRPCPrintChatMessageString(InChatMessageString);
	// 	}
	// }

	ANumberBaseballGameModeBase* NBGameModeBase = Cast<ANumberBaseballGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (NBGameModeBase)
	{
		NBGameModeBase->PrintChatMessageString(this, InChatBaseString, InChatMessageString);
	}
	
}

void ANumberBaseballPlayerController::ClientRPCPrintSystemMessageString_Implementation(const FString& InChatMessageString)
{
	PrintSystemMessageString(InChatMessageString);
}

void ANumberBaseballPlayerController::ClientRPCUpdateTimerWidget_Implementation(int Time)
{
	if (TimerWidgetInstance)
	{
		TimerWidgetInstance->UpdateTimerText(Time);
	}
}

void ANumberBaseballPlayerController::ClientRPCUpdateCurrentPlayerWidget_Implementation(const FString& PlayerName)
{
	if (TimerWidgetInstance)
	{
		TimerWidgetInstance->UpdateCurrentPlayer(PlayerName);
	}
}