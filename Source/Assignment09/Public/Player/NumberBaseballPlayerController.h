// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "NumberBaseballPlayerController.generated.h"

class UTimerWidget;
class UChatInput;
class UUserWidget;
/**
 * 
 */
UCLASS()
class ASSIGNMENT09_API ANumberBaseballPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ANumberBaseballPlayerController();
	
	void SetChatMessageString(const FString& InChatMessageString);
	void PrintChatMessageString(const FString& InChatMessageString);
	void PrintSystemMessageString(const FString& InChatMessageString);
	
	UFUNCTION(Client, Reliable)
	void ClientRPCPrintChatMessageString(const FString& InChatMessageString);
	UFUNCTION(Server, Reliable)
	void ServerRPCPrintChatMessageString(const FString& InChatBaseString, const FString& InChatMessageString);
	UFUNCTION(Client, Reliable)
	void ClientRPCPrintSystemMessageString(const FString& InChatMessageString);
	
	UFUNCTION(Client, Reliable)
	void ClientRPCUpdateTimerWidget(int Time);
	UFUNCTION(Client, Reliable)
	void ClientRPCUpdateCurrentPlayerWidget(const FString& PlayerName);
	
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UChatInput> ChatInputWidgetClass;
	UPROPERTY()
	TObjectPtr<UChatInput> ChatInputWidgetInstance;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> NotificationTextWidgetClass;
	UPROPERTY()
	TObjectPtr<UUserWidget> NotificationTextWidgetInstance;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> TimerWidgetClass;
	UPROPERTY()
	TObjectPtr<UTimerWidget> TimerWidgetInstance;
public:
	UPROPERTY(Replicated, BlueprintReadOnly)
	FText NotificationText;
	
private:
	FString ChatMessageString;
};
