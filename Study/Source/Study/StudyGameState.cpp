
#include "StudyGameState.h"
#include "Kismet/GameplayStatics.h"
#include "SpawnVolume.h"
#include "Item/CoinItem.h"
#include "StudyGameInstance.h"
#include "Study/StudyPlayerController.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Blueprint/UserWidget.h"

AStudyGameState::AStudyGameState()
{
	Score = 0;
	SpawnedCoinCount = 0;
	CollectedCoinCount = 0;
	WaveDuration = 30.f;
	CurrentLevelIndex = 0;
	MaxLevel = 3;
	CurrentWaveIndex = 0;
	MaxWave = 3;
	bIsAllLevelClear = false;
}

void AStudyGameState::BeginPlay()
{
	Super::BeginPlay();

	StartLevel();

	GetWorldTimerManager().SetTimer(HudUpdateTimerHandle, this, &AStudyGameState::UpdateHUD, 0.1f, true);
}

void AStudyGameState::AddScore(int32 Amount)
{
	if (UStudyGameInstance* GameInstance = Cast<UStudyGameInstance>(GetGameInstance()))
	{
		GameInstance->AddToScore(Amount);
	}

}

void AStudyGameState::StartLevel()
{
	if (AStudyPlayerController* Playercontroller = Cast<AStudyPlayerController>(GetWorld()->GetFirstPlayerController()))
	{
		Playercontroller->ShowGameHUD();
	}

	if (UStudyGameInstance* GameInstance = Cast<UStudyGameInstance>(GetGameInstance()))
	{
		CurrentLevelIndex = GameInstance->CurrentLevelIndex;
	}

	StartWave();

	//GetWorldTimerManager().SetTimer(WaveTimerHandle, this, &AStudyGameState::OnLevelTimeUp, WaveDuration, false);

}

void AStudyGameState::StartWave()
{
	CurrentWaveIndex++;

	SpawnedCoinCount = 0;
	CollectedCoinCount = 0;

	TArray<AActor*> FoundVolumes;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), FoundVolumes);

	int32 ItemToSpawn;

	if (CurrentWaveIndex == 1)
	{
		ItemToSpawn = 10;
		//WaveDuration = 10.f;
	}
	else if (CurrentWaveIndex == 2)
	{
		ItemToSpawn = 20;
		//WaveDuration = 20.f;
	}
	else if (CurrentWaveIndex == 3)
	{
		ItemToSpawn = 40;
		//WaveDuration = 30.f;
	}


	for (int i = 0; i < ItemToSpawn; i++)
	{
		if (FoundVolumes.Num() > 0)
		{
			ASpawnVolume* SpawnVolume = Cast<ASpawnVolume>(FoundVolumes[0]);
			if (SpawnVolume)
			{
				AActor* SpawnedActor = SpawnVolume->SpawnRandomItem();

				if (SpawnedActor && SpawnedActor->IsA(ACoinItem::StaticClass()))
				{
					SpawnedCoinCount++;
				}

			}
		}
	}

	GetWorldTimerManager().SetTimer(WaveTimerHandle, this, &AStudyGameState::OnWaveTimeUp, WaveDuration, false);
}

void AStudyGameState::OnWaveTimeUp()
{
	//EndLevel();
	OnGameOver();
}

void AStudyGameState::OnCoinCollected()
{
	CollectedCoinCount++;

	UE_LOG(LogTemp, Warning, TEXT("Coin Collected %d / %d"), CollectedCoinCount, SpawnedCoinCount);

	if (SpawnedCoinCount > 0 && CollectedCoinCount >= SpawnedCoinCount)
	{
		//EndLevel();

		EndWave();
	}
}

void AStudyGameState::EndLevel()
{
	GetWorldTimerManager().ClearTimer(WaveTimerHandle);

	if (CurrentLevelIndex >= MaxLevel)
	{
		OnGameOver();
		return;
	}

	if (UStudyGameInstance* GameInstance = Cast<UStudyGameInstance>(GetGameInstance()))
	{
		//AddScore(Score);
		//CurrentLevelIndex = GameInstance->CurrentLevelIndex;
		CurrentLevelIndex++;
		GameInstance->CurrentLevelIndex = CurrentLevelIndex;
		
	}
	
	if (LevelMapsNames.IsValidIndex(CurrentLevelIndex))
	{
		UGameplayStatics::OpenLevel(GetWorld(), LevelMapsNames[CurrentLevelIndex]);
	}
	else
	{
		bIsAllLevelClear = true;
		OnGameOver();
	}
}

void AStudyGameState::EndWave()
{
	GetWorldTimerManager().ClearTimer(WaveTimerHandle);

	if (CurrentWaveIndex >= MaxWave)
	{
		ShowEndLevelMenu();
	}
	else StartWave();
}

void AStudyGameState::OnGameOver()
{
	if (AStudyPlayerController* Playercontroller = Cast<AStudyPlayerController>(GetWorld()->GetFirstPlayerController()))
	{
		Playercontroller->SetPause(true);
		Playercontroller->ShowMainMenu(true);
	}	
}

void AStudyGameState::UpdateHUD()
{
	if (AStudyPlayerController* PlayerContrller = Cast<AStudyPlayerController>(GetWorld()->GetFirstPlayerController()))
	{
		if (UUserWidget* HUDWidget = PlayerContrller->GetHUDWidget())
		{
			PlayerContrller->UpdateDebuff();

			if (UTextBlock* TimeText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Time"))))
			{
				float RemainingTime = GetWorldTimerManager().GetTimerRemaining(WaveTimerHandle);
				TimeText->SetText(FText::FromString(FString::Printf(TEXT("Time: %.1f"), RemainingTime)));
			}

			if (UTextBlock* ScoreText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Score"))))
			{
				if (UStudyGameInstance* GameInstance = Cast<UStudyGameInstance>(GetGameInstance()))
				{
					Score = GameInstance->TotalScore;
				}

				ScoreText->SetText(FText::FromString(FString::Printf(TEXT("Scroe: %d"), Score)));
			}

			if (UTextBlock* LevelIndexText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Level"))))
			{
				LevelIndexText->SetText(FText::FromString(FString::Printf(TEXT("Level %d"), CurrentLevelIndex +1)));
			}

			if (UTextBlock* WaveIndexText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Wave"))))
			{
				WaveIndexText->SetText(FText::FromString(FString::Printf(TEXT("Wave %d"), CurrentWaveIndex)));
			}
			if (UTextBlock* CoinText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Coin"))))
			{
				CoinText->SetText(FText::FromString(FString::Printf(TEXT("%d/%d"),CollectedCoinCount, SpawnedCoinCount)));
			}

		}
	}
}

void AStudyGameState::ShowEndLevelMenu()
{
	if (AStudyPlayerController* PlayerContrller = Cast<AStudyPlayerController>(GetWorld()->GetFirstPlayerController()))
	{
		PlayerContrller->ShowPauseMenu(true);
	}
}


