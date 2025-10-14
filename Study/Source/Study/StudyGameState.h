// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "StudyGameState.generated.h"

/**
 * 
 */
UCLASS()
class STUDY_API AStudyGameState : public AGameState
{
	GENERATED_BODY()
public:
	AStudyGameState();
	
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = Score)
	int32 Score;
	UPROPERTY(VisibleAnywhere, Category = Coin)
	int32 SpawnedCoinCount;
	UPROPERTY(VisibleAnywhere, Category = Coin)
	int32 CollectedCoinCount;

	UPROPERTY(EditAnywhere, Category = Level)
	float WaveDuration;

	UPROPERTY(EditAnywhere, Category = Level)
	TArray<FName> LevelMapsNames;

	UFUNCTION(BlueprintCallable, Category = Score)
	void AddScore(int32 Amount);

	UFUNCTION(BlueprintPure, Category = Score)
	FORCEINLINE int32 GetScore() const { return Score; }

	UFUNCTION(BlueprintCallable, Category = Level)
	void OnGameOver();
	UFUNCTION(BlueprintCallable, Category = Level)
	void OnCoinCollected();

	FTimerHandle WaveTimerHandle;
	FTimerHandle HudUpdateTimerHandle;

	int32 CurrentLevelIndex;
	int32 MaxLevel;
	int32 CurrentWaveIndex;
	int32 MaxWave;

	bool bIsAllLevelClear;

	void StartLevel();
	void StartWave();
	void OnWaveTimeUp();
	void EndLevel();
	void EndWave();
	void UpdateHUD();
	void ShowEndLevelMenu();
};
