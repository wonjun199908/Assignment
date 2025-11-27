// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ChatInput.h"

#include "Components/EditableTextBox.h"
#include "Player/NumberBaseballPlayerController.h"


void UChatInput::NativeConstruct()
{
	Super::NativeConstruct();

	EditableTextBox_ChatInput->OnTextCommitted.AddDynamic(this, &UChatInput::OnChatInputTextCommitted);
}

void UChatInput::NativeDestruct()
{
	Super::NativeDestruct();

	EditableTextBox_ChatInput->OnTextCommitted.RemoveDynamic(this, &UChatInput::OnChatInputTextCommitted);
}

void UChatInput::OnChatInputTextCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	if (CommitMethod == ETextCommit::OnEnter)
	{
		ANumberBaseballPlayerController* PlayerController = Cast<ANumberBaseballPlayerController>(GetOwningPlayer());

		if (PlayerController)
		{
			PlayerController->SetChatMessageString(Text.ToString());

			EditableTextBox_ChatInput->SetText(FText());
		}
		
		
	}
}
