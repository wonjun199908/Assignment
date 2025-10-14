// Fill out your copyright notice in the Description page of Project Settings.


#include "StudyPlayerController.h"
#include "StudyCharacter.h"
#include "Blueprint/UserWidget.h"
#include "StudyGameState.h"
#include "StudyGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h" 
#include "Components/Button.h"
#include "Components/ProgressBar.h"
#include "Components/Border.h"
#include "Components/Image.h"
#include "Styling/SlateColor.h"
//#include "Item/DebuffData.h"
AStudyPlayerController::AStudyPlayerController()
{
	HUDWidgetClass = nullptr;
	HUDWidgetInstance = nullptr;

	MenuWidgetClass = nullptr;
	MenuWidgetInstance= nullptr;

	static ConstructorHelpers::FObjectFinder<UTexture2D>
		SlowTextureAsset(TEXT("/Game/Resources/Icon/snail.snail"));

	if (SlowTextureAsset.Succeeded())
	{
		SlowTexture = SlowTextureAsset.Object;
	}

	static ConstructorHelpers::FObjectFinder<UTexture2D>
		ReverseTextureAsset(TEXT("/Game/Resources/Icon/sync.sync"));

	if (ReverseTextureAsset.Succeeded())
	{
		ReverseTexture = ReverseTextureAsset.Object;
	}

	static ConstructorHelpers::FObjectFinder<UTexture2D>
		BlindTextureAsset(TEXT("/Game/Resources/Icon/hide.hide"));

	if (BlindTextureAsset.Succeeded())
	{
		BlindTexture = BlindTextureAsset.Object;
	}
}

void AStudyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FString CurrentMapName = GetWorld()->GetMapName();
	if (CurrentMapName.Contains("MenuLevel"))
	{
		ShowMainMenu(false);
	}
}




void AStudyPlayerController::ShowMainMenu(bool bIsRestart)
{
	if (HUDWidgetInstance)
	{
		HUDWidgetInstance->RemoveFromParent();
		HUDWidgetInstance = nullptr;
	}
	if (MenuWidgetInstance)
	{
		MenuWidgetInstance->RemoveFromParent();
		MenuWidgetInstance = nullptr;
	}

	RemovePauseMenu();

	if (MenuWidgetClass)
	{
		
		if (MenuWidgetInstance = CreateWidget<UUserWidget>(this, MenuWidgetClass))
		{
			MenuWidgetInstance->AddToViewport();

			bShowMouseCursor = true;
			bEnableClickEvents = true;
			bEnableMouseOverEvents = true;
			SetInputMode(FInputModeUIOnly());
		}
		if (UTextBlock* ButtonText = Cast<UTextBlock>(MenuWidgetInstance->GetWidgetFromName(TEXT("StartButtonText"))))
		{

			if (bIsRestart)
			{
				ButtonText->SetText(FText::FromString(TEXT("Restart")));
			}
			else
			{
				ButtonText->SetText(FText::FromString(TEXT("Start")));
			}
		}
		if (bIsRestart)
		{
			if (AStudyGameState* GameState = Cast<AStudyGameState>(UGameplayStatics::GetGameState(GetWorld())))
			{
				if (GameState->bIsAllLevelClear)
				{
					if (UTextBlock* GameOverText = Cast<UTextBlock>(MenuWidgetInstance->GetWidgetFromName(TEXT("GameOverText"))))
					{
						GameOverText->SetText(FText::FromString(TEXT("Congratulation!")));
					}
				}
			}

			if (UFunction* PlayAnimFunc = MenuWidgetInstance->FindFunction(FName("PlayGameOverAnim")))
			{
				MenuWidgetInstance->ProcessEvent(PlayAnimFunc, nullptr);
			}
			if (UTextBlock* TotalScoreText = Cast<UTextBlock>(MenuWidgetInstance->GetWidgetFromName(TEXT("TotalScoreText"))))
			{
				if (UStudyGameInstance* GameInstance = Cast<UStudyGameInstance>(GetWorld()->GetGameInstance()))
				{
					int32 TotalScore = GameInstance->TotalScore;

					TotalScoreText->SetText(FText::FromString(FString::Printf(TEXT("Total Score %d"), TotalScore)));
				}
			}
		}
		if (UButton* StartButton = Cast<UButton>(MenuWidgetInstance->GetWidgetFromName("StartButton")))
		{
			OnUnHoverMainWidgetStartButton();

			StartButton->OnClicked.AddDynamic(this, &AStudyPlayerController::OnClickMainWidgetStartButton);
			StartButton->OnHovered.AddDynamic(this, &AStudyPlayerController::OnHoverMainWidgetStartButton);
			StartButton->OnUnhovered.AddDynamic(this, &AStudyPlayerController::OnUnHoverMainWidgetStartButton);
		}
		if (UButton* ExitButton = Cast<UButton>(MenuWidgetInstance->GetWidgetFromName("ExitButton")))
		{
			OnUnHoverMainWidgetExitButton();

			ExitButton->OnClicked.AddDynamic(this, &AStudyPlayerController::OnClickMainWidgetExitButton);
			ExitButton->OnHovered.AddDynamic(this, &AStudyPlayerController::OnHoverMainWidgetExitButton);
			ExitButton->OnUnhovered.AddDynamic(this, &AStudyPlayerController::OnUnHoverMainWidgetExitButton);
		}
	}	

}

void AStudyPlayerController::ShowPauseMenu(bool bIsEndlevel)
{
	if (MenuWidgetInstance)
	{
		return;
	}

	if (PauseWidgetInstance)
	{
		PauseWidgetInstance->RemoveFromParent();
		PauseWidgetInstance = nullptr;
	}

	if (PauseWidgetClass)
	{
		PauseWidgetInstance = CreateWidget<UUserWidget>(this, PauseWidgetClass);

		if (PauseWidgetInstance)
		{
			PauseWidgetInstance->AddToViewport();

			SetPause(true);

			bShowMouseCursor = true;
			bEnableClickEvents = true;
			bEnableMouseOverEvents = true;
			SetInputMode(FInputModeUIOnly());
		}

		if (UButton* ResumeButton = Cast<UButton>(PauseWidgetInstance->GetWidgetFromName(TEXT("ResumeButton"))))
		{
			OnUnHoverPauseWidgetResumeButton();

			if (bIsEndlevel)
			{
				ResumeButton->OnClicked.AddDynamic(this, &AStudyPlayerController::OnClickPauseWidgetNextButton);
				if (UTextBlock* ButtonText = Cast<UTextBlock>(PauseWidgetInstance->GetWidgetFromName(TEXT("ResumeButtonText"))))
				{
					ButtonText->SetText(FText::FromString(TEXT("Next Level")));

					FSlateFontInfo Font = ButtonText->GetFont();
					Font.Size = 40.f;
					ButtonText->SetFont(Font);
				}

				if (UTextBlock* ButtonText = Cast<UTextBlock>(PauseWidgetInstance->GetWidgetFromName(TEXT("LevelText"))))
				{
					ButtonText->SetVisibility(ESlateVisibility::Visible);
				}
			}
			else
			{
				ResumeButton->OnClicked.AddDynamic(this, &AStudyPlayerController::OnClickPauseWidgetResumeButton);
				if (UTextBlock* ButtonText = Cast<UTextBlock>(PauseWidgetInstance->GetWidgetFromName(TEXT("ResumeButtonText"))))
				{
					ButtonText->SetText(FText::FromString(TEXT("Resume")));
				}
				if (UTextBlock* ButtonText = Cast<UTextBlock>(PauseWidgetInstance->GetWidgetFromName(TEXT("LevelText"))))
				{
					ButtonText->SetVisibility(ESlateVisibility::Hidden);
				}
			}
			
			ResumeButton->OnHovered.AddDynamic(this, &AStudyPlayerController::OnHoverPauseWidgetResumeButton);
			ResumeButton->OnUnhovered.AddDynamic(this, &AStudyPlayerController::OnUnHoverPauseWidgetResumeButton);
		}
		if (UButton* MenuButton = Cast<UButton>(PauseWidgetInstance->GetWidgetFromName(TEXT("MenuButton"))))
		{
			OnUnHoverPauseWidgetMenuButton();

			MenuButton->OnClicked.AddDynamic(this, &AStudyPlayerController::OnClickPauseWidgetMenuButton);
			MenuButton->OnHovered.AddDynamic(this, &AStudyPlayerController::OnHoverPauseWidgetMenuButton);
			MenuButton->OnUnhovered.AddDynamic(this, &AStudyPlayerController::OnUnHoverPauseWidgetMenuButton);
		}
		if (UButton* QuitButton = Cast<UButton>(PauseWidgetInstance->GetWidgetFromName(TEXT("ExitButton"))))
		{
			OnUnHoverMainWidgetExitButton();

			QuitButton->OnClicked.AddDynamic(this, &AStudyPlayerController::OnClickMainWidgetExitButton);
			QuitButton->OnHovered.AddDynamic(this, &AStudyPlayerController::OnHoverMainWidgetExitButton);
			QuitButton->OnUnhovered.AddDynamic(this, &AStudyPlayerController::OnUnHoverMainWidgetExitButton);
		}
	}
}

void AStudyPlayerController::RemovePauseMenu()
{
	if (PauseWidgetInstance)
	{
		PauseWidgetInstance->RemoveFromParent();
		PauseWidgetInstance = nullptr;

		SetPause(false);

		bShowMouseCursor = false;
		SetInputMode(FInputModeGameOnly());
	}
}

void AStudyPlayerController::OpenMenuLevel()
{
	UE_LOG(LogTemp, Error, TEXT("open menu level"))


	UGameplayStatics::OpenLevel(GetWorld(), FName("MenuLevel"));
}

void AStudyPlayerController::StartGame()
{

	if (UStudyGameInstance* GameInstance = Cast<UStudyGameInstance>(GetGameInstance()))
	{
		GameInstance->CurrentLevelIndex = 0;
		GameInstance->TotalScore = 0;
	}

	UGameplayStatics::OpenLevel(GetWorld(), FName("BasicLevel"));

	if (AStudyGameState* GameState = Cast<AStudyGameState>(UGameplayStatics::GetGameState(GetWorld())))
	{
		GameState->StartLevel();
	}
	

}

void AStudyPlayerController::ShowGameHUD()
{

	if (HUDWidgetInstance)
	{
		HUDWidgetInstance->RemoveFromParent();
		HUDWidgetInstance = nullptr;
	}
	if (MenuWidgetInstance)
	{
		MenuWidgetInstance->RemoveFromParent();
		MenuWidgetInstance = nullptr;
	}

	if (HUDWidgetClass)
	{
		HUDWidgetInstance = CreateWidget<UUserWidget>(this, HUDWidgetClass);
		if (HUDWidgetInstance)
		{
			HUDWidgetInstance->AddToViewport();

			bShowMouseCursor = false;
			SetInputMode(FInputModeGameOnly());

		}

		if (AStudyGameState* GameState = Cast<AStudyGameState>(GetWorld()->GetGameState()))
		{
			GameState->UpdateHUD();
		}

	}
}

void AStudyPlayerController::OnClickMainWidgetStartButton()
{
	StartGame();
}

void AStudyPlayerController::OnHoverMainWidgetStartButton()
{
	OnHoverButton(MenuWidgetInstance, "StartButton", "StartButtonText");
}

void AStudyPlayerController::OnUnHoverMainWidgetStartButton()
{
	
	OnUnHoverButton(MenuWidgetInstance, "StartButton", "StartButtonText");

}

void AStudyPlayerController::OnClickMainWidgetExitButton()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), this,EQuitPreference::Quit, true);
}

void AStudyPlayerController::OnHoverMainWidgetExitButton()
{
	if (MenuWidgetInstance)
	{
		OnHoverButton(MenuWidgetInstance, "ExitButton", "ExitButtonText");
	}
	else if (PauseWidgetInstance)
	{
		OnHoverButton(PauseWidgetInstance, "ExitButton", "ExitButtonText");
	}

	

}

void AStudyPlayerController::OnUnHoverMainWidgetExitButton()
{
	if (MenuWidgetInstance)
	{
		OnUnHoverButton(MenuWidgetInstance, "ExitButton", "ExitButtonText");
	}
	else if (PauseWidgetInstance)
	{
		OnUnHoverButton(PauseWidgetInstance, "ExitButton", "ExitButtonText");
	}
}

void AStudyPlayerController::OnClickPauseWidgetNextButton()
{
	if (AStudyGameState* GameState = Cast<AStudyGameState>(UGameplayStatics::GetGameState(GetWorld())))
	{
		GameState->EndLevel();
	}
}

void AStudyPlayerController::OnClickPauseWidgetResumeButton()
{
	RemovePauseMenu();
}

void AStudyPlayerController::OnHoverPauseWidgetResumeButton()
{
	OnHoverButton(PauseWidgetInstance, "ResumeButton", "ResumeButtonText");
}

void AStudyPlayerController::OnUnHoverPauseWidgetResumeButton()
{
	OnUnHoverButton(PauseWidgetInstance, "ResumeButton", "ResumeButtonText");
}

void AStudyPlayerController::OnClickPauseWidgetMenuButton()
{
	OpenMenuLevel();
}

void AStudyPlayerController::OnHoverPauseWidgetMenuButton()
{
	OnHoverButton(PauseWidgetInstance, "MenuButton", "MenuButtonText");
}

void AStudyPlayerController::OnUnHoverPauseWidgetMenuButton()
{
	OnUnHoverButton(PauseWidgetInstance, "MenuButton", "MenuButtonText");
}



void AStudyPlayerController::OnHoverButton(UUserWidget* Widget, FName WidgetButtonName, FName WidgetButtonTextName) const
{
	if (UButton* Button = Cast<UButton>(Widget->GetWidgetFromName(WidgetButtonName)))
	{
		Button->SetBackgroundColor(FLinearColor(0.f, 0.f, 0.f, 1.f));
	}
	if (UTextBlock* ButtonText = Cast<UTextBlock>(Widget->GetWidgetFromName(WidgetButtonTextName)))
	{
		ButtonText->SetColorAndOpacity(FSlateColor(FLinearColor(1.f, 1.f, 1.f, 1.f)));
	}
}

void AStudyPlayerController::OnUnHoverButton(UUserWidget* Widget, FName WidgetButtonName, FName WidgetButtonTextName) const
{
	if (UButton* Button = Cast<UButton>(Widget->GetWidgetFromName(WidgetButtonName)))
	{
		Button->SetBackgroundColor(FLinearColor(0.f, 0.f, 0.f, 0.5f));
	}
	if (UTextBlock* ButtonText = Cast<UTextBlock>(Widget->GetWidgetFromName(WidgetButtonTextName)))
	{
		ButtonText->SetColorAndOpacity(FSlateColor(FLinearColor(1.f, 1.f, 1.f, 0.5f)));
	}
}


void AStudyPlayerController::UpdateDebuff()
{
	if (AStudyCharacter* PlayerCharacter = Cast<AStudyCharacter>(GetCharacter()))
	{
		TMap<EDebuffType, FTimerHandle> Debuffs = PlayerCharacter->GetActiveDebuffs();

		
		for (int32 i = 0; i < 3; ++i)
		{
			FName ProgressBarName = FName(FString::Printf(TEXT("Debuff%d"), i));
			FName ImageName = FName(FString::Printf(TEXT("DebuffImage%d"), i));

			if (UProgressBar* ProgressBar = Cast<UProgressBar>(HUDWidgetInstance->GetWidgetFromName(ProgressBarName)))
			{
				ProgressBar->SetVisibility(ESlateVisibility::Hidden);
				ProgressBar->SetPercent(0.0f);
			}
			if (UImage* Image = Cast<UImage>(HUDWidgetInstance->GetWidgetFromName(ImageName)))
			{
				Image->SetVisibility(ESlateVisibility::Hidden);
			}

		}
 
		int num = 0;

		for (const TPair<EDebuffType, FTimerHandle>& Pair : Debuffs)
		{
			EDebuffType DebuffType = Pair.Key;
			FTimerHandle TimerHandle = Pair.Value;

			float RemainTime = GetWorldTimerManager().GetTimerRemaining(TimerHandle);

			if (HUDWidgetInstance)
			{
				FName ProgressBarName = FName(FString::Printf(TEXT("Debuff%d"), num));
				FName ImageName = FName(FString::Printf(TEXT("DebuffImage%d"), num));


				if (UImage* Image = Cast<UImage>(HUDWidgetInstance->GetWidgetFromName(ImageName)))
				{
					Image->SetVisibility(ESlateVisibility::Visible);

					switch (DebuffType)
					{
					case EDebuffType::Slow:
						
						if (SlowTexture)
						{
							Image->SetBrushFromTexture(SlowTexture);
						}

						break;
					case EDebuffType::ReverseController:

						if (SlowTexture)
						{
							Image->SetBrushFromTexture(ReverseTexture);
						}


						break;
					case EDebuffType::Blind:

						if (SlowTexture)
						{
							Image->SetBrushFromTexture(BlindTexture);
						}
						break;
					default:
						continue;
					}
				}



				if (UProgressBar* ProgressBar = Cast<UProgressBar>(HUDWidgetInstance->GetWidgetFromName(ProgressBarName)))
				{

					ProgressBar->SetVisibility(ESlateVisibility::Visible);
					ProgressBar->SetPercent(RemainTime / 5.f);

					if (RemainTime <= 0.01)
					{
						ProgressBar->SetVisibility(ESlateVisibility::Hidden);
					}
				}
			}

			num++;
		}
	}
}

void AStudyPlayerController::BlindAnim()
{
	UE_LOG(LogTemp, Error, TEXT("Controller1"));

	if (HUDWidgetInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("Controller2"));
		
		if (UFunction* PlayBlindAnim = HUDWidgetInstance->FindFunction(FName("PlayBlindAnim")))
		{
			HUDWidgetInstance->ProcessEvent(PlayBlindAnim, nullptr);
		}
		
	}
}

